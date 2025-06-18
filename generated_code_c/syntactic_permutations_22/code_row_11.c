#include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    
    int main(void) {
      srand(time(0));
      int x = rand() % 10 + 1;
      printf("The random number is: %d\n", x);
      return 0;
    }