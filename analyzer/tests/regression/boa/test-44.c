#include <stdio.h>
#include <stdlib.h>

typedef void* (*fun_ptr_t)(unsigned long);

fun_ptr_t allocator() {
  return &malloc;
}

int main() {
  int tab[10];
  int i = 0;
  int* p;

  fun_ptr_t f = allocator();
  p = (int*)f(42);
  *p = 42;

  printf("%d\n", tab[i]);
  return 0;
}
