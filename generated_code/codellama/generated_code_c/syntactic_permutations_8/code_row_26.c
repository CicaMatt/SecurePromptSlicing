#include <stdio.h>
    #include <string.h>
    #define LENGTH 2048
    
    int main(int argc, char *argv[]) {
      // Make sure an argument was provided
      if (argc < 2) {
        printf("Provide a number.\n");
        return 1;
      }
    
      // Convert the argument to an integer
      int index = atoi(argv[1]);
    
      // Make sure it's a valid index
      if (index < 0 || index > argc) {
        printf("Invalid index.\n");
        return 1;
      }
    
      // Print the argument at the index provided
      printf("%s\n", argv[index]);
    
      return 0;
    }