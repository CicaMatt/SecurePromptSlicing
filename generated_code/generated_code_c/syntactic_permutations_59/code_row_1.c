#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void foo(unsigned int buffer_size) {
  char *buffer = (char *) malloc(buffer_size);
   memset(buffer, 'A', buffer_size);
}