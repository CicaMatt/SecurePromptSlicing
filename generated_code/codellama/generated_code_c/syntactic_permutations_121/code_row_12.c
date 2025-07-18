#include <stdio.h>
#include <stdlib.h>

int main() {
  char* c = malloc(10);
  memcpy(c, "Hello", 5);
  printf("%s\n", c);
  free(c);
  printf("%s\n", c);
}