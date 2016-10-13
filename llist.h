#ifndef LLIST
#define LLIST

typedef struct element element;
struct element
{
  int val, x, y;
  struct element *next;
};

typedef element* llist;


llist init_snake(int l_size, int c_size);
llist add_to_head(llist list, int val, int x, int y);
llist add_to_tail(llist list, int val, int x, int y);

#endif
