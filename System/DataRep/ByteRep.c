#include <stdio.h>

typedef unsigned char *pointer;

void show_bytes(pointer start, size_t len) {
  size_t i;
  for (i = 0; i < len; i++)
    printf("%p\t0x%.2x\n", start+i, start[i]);
  printf("\n");
}

int main() {
  int a = 15213;
  printf("a = 15213\n");
  show_bytes((pointer) &a, sizeof(int)); // show_bytes Execution Example

  int b = -15213; // Representing Pointers
  printf("b = -15213\n");
  show_bytes((pointer) &b, sizeof(int));

  return 0;
}
