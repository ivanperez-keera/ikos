#include <stdio.h>

extern int unknown();

// gcc test-8.c -Wuninitialized -o test-8
// gcc does not report any warning.

// uno test-8.c: uno: in fct main, possibly uninitialized variable 'x'

// this test is biased by the compiler. It should be unsafe but ikos reports
// safe.
int main(int argc, char** argv) {
  argc = unknown();

  if (argc < 0)
    return 42;

  int x, y;
  if (argc == 0)
    x = 0;
  else if (argc == 1)
    x = 1;
  else if (argc > 2)
    x = 2;

  return x;
}
