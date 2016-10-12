#ifndef LLIST
#define LLIST

typedef struct element element;
struct element
{
  int val;
  struct element *next;
};

typedef element* llist;


llist add_to_head(llist list, int val);
llist add_to_tail(llist list, int val);

#endif
