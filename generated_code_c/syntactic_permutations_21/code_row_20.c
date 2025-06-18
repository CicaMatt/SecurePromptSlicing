#include <stdio.h>
    
    int main(int argc, char *argv[]) {
      // Get the number from the command line
      int num = atoi(argv[1]);
    
      // Add 1000 to it
      num += 1000;
    
      // Print the result
      printf("%d\n", num);
    
      return 0;
    }