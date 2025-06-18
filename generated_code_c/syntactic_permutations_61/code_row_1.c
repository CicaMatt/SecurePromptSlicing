#include <stdlib.h>
    
    int main(void) {
      int *buffer;
      int i = 0;
      int j = 0;
      int buffer_size = 1024;
      buffer = (int *)malloc(sizeof(int) * buffer_size);
      for (i = 0; i < buffer_size; i++) {
        for (j = 0; j < buffer_size; j++) {
          free(buffer[i]);
        }
      }
    }