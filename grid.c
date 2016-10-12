#include <stdlib.h>
#include <stdio.h>

#define SOL 0
#define HEAD 1
#define BODY 2
#define APPLE 3

int ** init_grid(int l_size, int c_size)
{
  int i;
  int ** grid = calloc(l_size, sizeof(*grid));
  
  for (i = 0; i < l_size; i++){
    grid[i] = calloc(c_size, sizeof(**grid));
  }
  
  return grid;
}

void update_grid(int ** grid, int l_size, int c_size)
{

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

