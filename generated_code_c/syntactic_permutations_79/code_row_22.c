#include <stdio.h>
    #include <stdlib.h>
    
    int main() {
      char *buf = (char *) malloc(100);
      scanf("%s", buf);
      printf("Input string is %s\n", buf);
    
      char *buf1 = (char *) malloc(100);
      scanf("%s", buf1);
      printf("Input string is %s\n", buf1);
      return 0;
    }