/***********************************************************           
 * main.c -- A implementation of the snake game in c       *
 *                                                         *   
 *                                                         *   
 * Author:  Jean-Hugo OUWE MISSI OUKEM                     *   
 *                                                         *   
 * Purpose:  Simple snake in order to learn pointer and    *
 *           linked list in c                              *
 *                                                         *   
 *                                                         *   
 *                                                         *   
 ***********************************************************/

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "grid.h"
#include "llist.h"
#include "input.h"
#include "signal.h"

#define SNAKE_SIZE_BEGIN 3

int is_integer(char *string)
{
  char c;
  int i;

  for(i = 0; string[i] != 0; i++){
      c = string[i];
      if(c < '0' || c > '9'){
          return 0;
      }
  }
  return 1;
}

void handle_arg(int argc, char **argv, int *l_size, int *c_size, int *update_time)
{
  char * options = "r:c:t:h";
  char current_option;
  char help[512];

  snprintf(help, 512, "Usage\n %s [OPTIONS]\n\nThe following options are availables:\n"
  "-h,          Show this help menu\n"
  "-r,          Set the number of row (5 min)\n"
  "-c,          Set the number of colomns (5 min)\n"
  "-t,          Set the time between each frame update (in microseconds)\n", argv[0]);

  while((current_option = getopt(argc, argv, options)) != -1){
    int *opt_addr;    
    switch(current_option){    
        case 'r': opt_addr = l_size; break;
        case 'c': opt_addr = c_size; break;
        case 't': opt_addr = update_time; break;
        case 'h': printf("%s", help); exit(0);
    }
    if(optarg != NULL){
        // The argument is a valid integer.
        if(is_integer(optarg)){
            if((current_option == 'r' || current_option == 'c') && (atoi(optarg) < 5)){
              fprintf(stderr, "Error: The minimum size for -%c is 5.\n", current_option);
              exit(-1);
            }
            if(current_option == 't' && (atoi(optarg) < 0)){
              fprintf(stderr, "Error: The value for -%c sould be positive.\n", current_option);
              exit(-1);
            }
        *opt_addr = atoi(optarg);
        } else {
            fprintf(stderr, "Error: The value for -%c should be an integer.\n", current_option);
            exit(-1);
        }
    } else {
        exit(-1);
    }
  }


}


int main(int argc, char * argv[]){

  int l_size, c_size, snake_size, update_time, status;
  int ** grid;
  llist snake;
  input_arg * input_arg = NULL;
  pthread_t input_handling;
  input_arg = NULL;
  init_input_arg(&input_arg);

  // Set the default options.
  l_size = c_size = 15;
  update_time = 100;  

  // Get the user options.
  handle_arg(argc, argv, &l_size, &c_size, &update_time);

  // Initialiaze the game data.
  grid = init_grid(l_size, c_size);
  snake = init_snake(l_size, c_size, grid);
  snake_size = SNAKE_SIZE_BEGIN;
  status = 0;

  // Handle the input.
  if(pthread_create(&input_handling, NULL, handle_input, (void *) input_arg)){
    perror("pthread_create");
    exit(1);
  }
  
  // Handle the signals.
  set_sig_handler();
  
  // Game loop.
  while(!status){  
    
    status = update_grid(grid, l_size, c_size, &snake, &snake_size, input_arg);
    clear_screen();    
    display_grid(grid, l_size, c_size);
    if(status != 0){
      break;
    }
    usleep(update_time * 1000);
  }
  
  // Stop the thread.
  input_arg->stop = 1;
  
  if(pthread_join(input_handling, NULL)){
    perror("pthread_join");
    exit(1);
  }
  
  if(status > 0){
    printf("Congratulation you ate all the apple!\n");
  } else {
    printf("Game Over\n");
  }
  printf("Your final length was %d.\n", snake_size);

  free_grid(grid, l_size);
  free_llist(snake);
  
  return 0;
}
