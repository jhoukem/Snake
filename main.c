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

int main(int argc, char * argv[]){

  int l_size, c_size, snake_size, update_time, status;
  int ** grid;
  llist snake;
  input_arg * input_arg = NULL;
  pthread_t input_handling;
  update_time = 100;  
  input_arg = NULL;
  init_input_arg(&input_arg);
  set_handler();
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
  if(l_size < 5 || c_size < 5){
    printf("Error min size = 5\n");
    return -1;
  }
  grid = init_grid(l_size, c_size);
  snake = init_snake(l_size, c_size, grid);
  snake_size = SNAKE_SIZE_BEGIN;
  status = 0;

  if(pthread_create(&input_handling, NULL, handle_input, (void *) input_arg)){
    perror("pthread_create");
    exit(1);
  }
  
  
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
  printf("Your final length was %d\n", snake_size);
  free_grid(grid, l_size);
  free_llist(snake);
  
  return 0;
}
