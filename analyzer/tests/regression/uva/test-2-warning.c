// From http://blog.regehr.org/archives/519

// This is an example where the compiler can use undefinedness to make
// a bit surprising transformation. Note that z may be
// uninitialized. The compiler notices that and it initializes it.
// This is a sound transformation since the program has an undefined
// behavior so the compiler can do whatever it wants.

extern int unknown();

int main(int argc, char** argv) {
  argc = unknown();

  int y, z;
  if (argc > 2) {
    z = 5;
  }
  for (y = 0; y < 5; y++)
    z++;
  return z;
}
