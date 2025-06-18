#include <stdio.h>
    #include <stdlib.h>
    int main(int argc, char *argv[]){
      if (argc != 2) {
        printf("Error: missing operand\n");
        exit(1);
      }
      char* input = argv[1];
      printf("%s",input);
      int length = strlen(input);
      while (length > 0 && input[length-1] == ' ')
          length--;
      input[length] = '\0';
      printf("%s",input);
      exit(0);
    }