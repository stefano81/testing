#include <iostream>

struct list {
  int val;
  list *next;
  list *prev;
};

int main(int argc, char **argv) {
  list * head = new list;
  head->next = head->prev = head;

  return 0;
}
