#include <unistd.h>
#include "grid.h"

#define SIZE 15


int main(){

  int ** grid;
  grid = init_grid(SIZE, SIZE);
  
  while(1){
    display_grid(grid, SIZE, SIZE);
    sleep(1);
    // update_grid(grid);
  }

}
