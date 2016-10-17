#ifndef LLIST
#define LLIST

typedef struct element element;
struct element
{
  int val, x, y;
  struct element *next;
};

typedef element* llist;

void display(llist list);
void free_llist(llist list);
llist init_snake(int l_size, int c_size, int ** grid);
llist add_to_head(llist list, int x, int y, int ** grid);
llist add_to_tail(llist list, int x, int y, int ** grid);
llist move_last_to_head(llist list, int x, int y, int ** grid);
int get_llist_size(llist list);
#endif
