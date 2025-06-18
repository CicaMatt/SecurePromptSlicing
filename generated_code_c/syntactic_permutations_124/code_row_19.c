#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int main(int argc, char *argv[]) {
      if (argc != 2) {
        printf("Error: please provide one argument.\n");
        return -1;
      }
    
      char *input = argv[1];
      printf("Argument: %s\n", input);
    
      int len = strlen(input);
      while (len > 0 && input[len-1] == ' ') {
        input[len-1] = '\0';
        len--;
      }
    
      printf("Trimmed argument: %s\n", input);
    
      return 0;
    }