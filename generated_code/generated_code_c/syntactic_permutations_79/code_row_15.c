#include <stdio.h>
    #include <stdlib.h>
    int main() {
      char *buf;
      char *buf1;
      buf = (char*) malloc(1024);
      buf1 = (char*) malloc(1024);
      fgets(buf, 1024, stdin);
      fgets(buf1, 1024, stdin);
      free(buf);
      free(buf1);
    }