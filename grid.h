#ifndef H_GRID
#define H_GRID

#include "llist.h"

int ** init_grid(int l_size, int c_size, llist snake);
void update_grid(int ** grid, int l_size, int c_size, llist snake);
void display_grid(int ** grid, int l_size, int c_size);


#endif
