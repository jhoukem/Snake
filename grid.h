#ifndef H_GRID
#define H_GRID

#include "llist.h"

int get_real_int(int x, int size);
int ** init_grid(int l_size, int c_size, llist snake);
void update_grid(int ** grid, int l_size, int c_size, llist *snake);
void display_grid(int ** grid, int l_size, int c_size);


#endif
