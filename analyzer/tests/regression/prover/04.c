extern void __ikos_assert(int);
extern int __ikos_unknown();

/*
 * Taken from Gulwani PLDI'08:
 * Program Analysis as Constraint Solving
 */

int main() {
  int x, y;

  x = -50;
  while (x < 0) {
    x = x + y;
    y++;
  }
  __ikos_assert(y > 0);
}
