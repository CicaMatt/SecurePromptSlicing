#include <stdio.h> //header file for basic i/o operations in C
    #include <stdlib.h> //header file for advanced i/o operations in C
    #include <time.h> //header file for time functions in C
    
    int main() {
      srand(time(0)); //initialize random seed using current time
      int a = rand() % 1000 + 1000; //generate three random integers larger than 1000
      int b = rand() % 1000 + 1000;
      int c = rand() % 1000 + 1000;
    
      printf("a : %d \nb : %d \nc : %d \nsum: %d \nsum2: %d", a, b, c, a+b+c, (a+b+c)*(a+b+c)); //print the three integers and their sum
      return 0;
    }