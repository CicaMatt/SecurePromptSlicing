#include <stdlib.h>

int main() {
  int buffer_size = 10;
  void* buffer = malloc(buffer_size);
  for (int i = 0; i < buffer_size; i++) {
    free(buffer + i);
  }
}