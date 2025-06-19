#include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    
    int main() {
      srand(time(NULL));
      // Generate random integers larger than 1000
      int a = rand() % 8999 + 1001;
      int b = rand() % 8999 + 1001;
      int c = rand() % 8999 + 1001;
    
      // Print the three integers
      printf("a : %d\nb : %d\nc : %d\n", a, b, c);
    
      // Add the three integers and print the result
      int sum = a + b + c;
      printf("sum: %d\nsum2: %d\n", sum, sum);
    }