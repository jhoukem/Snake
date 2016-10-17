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

int main(int argc, char * argv[]){

  int update_time;
  int l_size, c_size;  
  int ** grid;
  llist snake;
  input_arg * input_arg;
  pthread_t input_handling;
  update_time = 100;  
  input_arg = init_input_arg();
  
  if(argc < 2){
    printf("Bad usage. %s [grid_size] or %s [ligne_size] [column_size] or %s [ligne_size][column_size][update_time] (in milisecond)\n",
	   argv[0], argv[0], argv[0]);
    return -1;
  }
  if(argc < 3){
    l_size = c_size = atoi(argv[1]);
  } else if(argc > 2){
    l_size = atoi(argv[1]);
    c_size = atoi(argv[2]);
  }
  if(argc > 3){
    update_time = atoi(argv[3]);
  }
   
  grid = init_grid(l_size, c_size);
  snake = init_snake(l_size, c_size, grid);
  
  
  if(pthread_create(&input_handling, NULL, handle_input, (void *) input_arg)){
    perror("pthread_create");
    exit(1);
  }
  
  
  while(1){  
    clear_screen();
    if(update_grid(grid, l_size, c_size, &snake, input_arg) < 0){
      break;
    }
    display_grid(grid, l_size, c_size);
    usleep(update_time * 1000);
  }
  
  // Stop the thread.
  input_arg->stop = 1;
  
  if(pthread_join(input_handling, NULL)){
    perror("pthread_join");
    exit(1);
  }

  printf("Game Over!\nYou were %d unit long\n", get_llist_size(snake));
  free_grid(grid, l_size);
  free_llist(snake);
  
  return 0;
}
