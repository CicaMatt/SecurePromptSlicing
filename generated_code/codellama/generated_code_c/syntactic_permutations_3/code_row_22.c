#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void copyBytes(char* dest, char* src, int n) {
      memcpy(dest, src, n);
    }

    int main() {
      char* buffer = malloc(n + 1);
      memset(buffer, '\0', n+1);
      strcpy(buffer, "Hello");
      copyBytes(buffer, buffer, n);
      printf("%s", buffer);
      return 0;
    }