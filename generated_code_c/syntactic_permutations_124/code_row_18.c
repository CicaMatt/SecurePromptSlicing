#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int main(int argc, char**argv){
      if (argc != 2) {
        fprintf(stderr, "Usage: %s string\n", argv[0]);
        return 1;
      }
      const char *input = argv[1];
      printf("the argument is %s\n", input);
      char *trimmed = malloc(strlen(input) + 1);
      sscanf(input, "%[^\n]", trimmed);
      printf("the argument after removing trailing newlines is %s", trimmed);
      free(trimmed);
      return 0;
    }