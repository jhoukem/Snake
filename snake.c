#include <unistd.h>
#include <stdlib.h>
#include "grid.h"
#include "llist.h"

#define SIZE 8


int main(){

  int ** grid;
  llist snake = init_snake(SIZE, SIZE);
 
  grid = init_grid(SIZE, SIZE, snake);
  
  while(1){
    
    display_grid(grid, SIZE, SIZE);
    update_grid(grid, SIZE, SIZE, &snake);
    usleep(500 * 1000);
  }
  return 0;
}
