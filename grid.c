#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "llist.h"
#include "input.h"

#define SOL 0
#define HEAD 1
#define BODY 2
#define APPLE 3

int food = 0;

void free_grid(int ** grid, int l_size)
{
  int i;
  for(i = 0; i < l_size; i++){
    free(grid[i]);
  }
  free(grid);
}


int ** init_grid(int l_size, int c_size)
{
  int i;
  int ** grid = calloc(l_size, sizeof(*grid));
  
  for (i = 0; i < l_size; i++){
    grid[i] = calloc(c_size, sizeof(**grid));
  }
  
  return grid;
}

int get_real_int(int x, int size)
{
  if(x < 0){
    return size -1;
  }
  return x % size;
}

void pop_food(int ** grid, int l_size, int c_size){
  int x, y;
  srand(time(NULL));

  do {
    x = rand() % c_size;
    y = rand() % l_size;
  }
  while(grid[y][x] != SOL);

  grid[y][x] = APPLE;
  food++;
  
}

int update_grid(int ** grid, int l_size, int c_size, llist * snake, input_arg * input_arg)
{
  // display(*snake);
  int next_x, next_y, x_input, y_input, sem_value;
  sem_value = 1;
  
  x_input = input_arg->x;
  y_input = input_arg->y;
    
  next_x = get_real_int((*snake)->x + x_input, c_size);
  next_y = get_real_int((*snake)->y + y_input, l_size);
  
  int destination = grid[next_y][next_x];
  // printf("dest = %d\n", destination);
  switch(destination){
  case BODY: return -1;// The snake has collide
  case APPLE:   
    *snake = add_to_head(*snake, next_x, next_y, grid);
    food--;
    break;
  default:
     *snake = move_last_to_head(*snake, next_x, next_y, grid); 
    break;
  } 

  if(!food){
    pop_food(grid, l_size, c_size);
  }
  
  // allow to capture another input
  sem_getvalue(&input_arg->sem, &sem_value);
  if(sem_value == 0){
    sem_post(&input_arg->sem);  
  }
  
  return 0; 
}

/**
 * Display the grid, change the output here.
 */
void display_grid(const int ** grid, int l_size, int c_size)
{
  int i, j;
  for (i = 0; i < l_size; i++){
    for (j = 0; j < c_size; j++){
      if(grid[i][j] == SOL){
	printf(".");
      } else if(grid[i][j] == APPLE){
	printf("x");
      } else if(grid[i][j] == BODY){
	printf("°");
      } else if(grid[i][j] == HEAD){
	printf("0");
      }     
    }
    printf("\n");
  } 
  printf("\n"); 
}

void clear_screen()
{
  const char* CLEAR_SCREE_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO,CLEAR_SCREE_ANSI, 11);
}

