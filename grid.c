#include <stdlib.h>
#include <stdio.h>
#include "llist.h"

#define SOL 0
#define HEAD 1
#define BODY 2
#define APPLE 3

int ** init_grid(int l_size, int c_size, llist snake)
{
  int i;
  int ** grid = calloc(l_size, sizeof(*grid));
  
  for (i = 0; i < l_size; i++){
    grid[i] = calloc(c_size, sizeof(**grid));
  }

  while(snake != NULL){
    grid[snake->y][snake->x] = snake->val;
    snake = snake->next;
  }
  
  return grid;
}

void update_grid(int ** grid, int l_size, int c_size, llist snake)
{
  element* elem = snake;
  int x, y;

  grid[elem->y][elem->x] = SOL;
  
  while(elem->next != NULL){
 
    elem->x = elem->next->x ;
    elem->y = elem->next->y ;
    grid[elem->y][elem->x] = elem->val;
    elem = elem->next;
  }
  
  // Move the head
  elem->x = (elem->x + 1)%(c_size - 1);
  grid[elem->y][elem->x]= elem->val;
      
}

/**
 * Display the grid, change the output here.
 */
void display_grid(int ** grid, int l_size, int c_size)
{
  int i, j;
  for (i = 0; i < l_size; i++){
    for (j = 0; j < c_size; j++){
      if(grid[i][j] == SOL){
	printf(".");
      } else if(grid[i][j] == APPLE){
	printf("x");
      } else if(grid[i][j] == BODY){
	printf("*");
      } else if(grid[i][j] == HEAD){
	printf("O");
      }     
    }
    printf("\n");
  } 
  printf("\n"); 
}

