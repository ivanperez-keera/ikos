#include <stdio.h>

extern int unknown();

void foo(int vsupply, int LOW_BATTERY_DECIVOLT) {
  static int t = 0;
  if (vsupply < LOW_BATTERY_DECIVOLT)
    t++;
  else
    t = 0;

  printf("%d\n", t);
}

int main(int argc, char** argv) {
  foo(unknown(), unknown());
  return 42;
}
