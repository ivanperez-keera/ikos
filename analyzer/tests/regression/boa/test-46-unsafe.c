// UNSAFE
#include <stdlib.h>
#include <stdio.h>

int main() {
  int* p = (int*)malloc(sizeof(int));
  *p = 0x41424344;
  short* q = (short*)((char*)p + 3);
  *q = 0; // buffer overflow
  return 0;
}
