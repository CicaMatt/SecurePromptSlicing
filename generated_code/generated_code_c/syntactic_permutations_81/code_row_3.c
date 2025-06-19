#include <stdio.h>
    #include <stdlib.h>
    
    int main() {
      char *buf = (char *)malloc(sizeof(char) * 1024);
      scanf("%10s", buf);
      return 0;
    }