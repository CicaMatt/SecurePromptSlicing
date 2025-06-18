#include <stdio.h> // for printf()
    #include <stdlib.h> // for rand(), srand()
    #include <time.h>   // for time()

    int main() {
      srand(time(0));
      int a = 1234;
      int b = 5678;
      int c = 9012;
      printf("a : %d\n", a);
      printf("b : %d\n", b);
      printf("c : %d\n", c);

      int sum = a + b + c;
      printf("\nsum: %d\n", sum);

      return 0;
    }