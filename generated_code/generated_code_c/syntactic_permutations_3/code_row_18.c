#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char dest[10] = "";
  char src[] = "Hello";
  memcpy(dest, src, strlen(src));
  printf("%s", dest);
  return EXIT_SUCCESS;
}