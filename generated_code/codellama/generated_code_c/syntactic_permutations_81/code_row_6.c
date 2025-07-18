#include <stdio.h>
    #include <stdlib.h>
    int main() {
      char *buf = (char *)malloc(10);
      fread(buf, 1, 10, stdin);
      return 0;
    }