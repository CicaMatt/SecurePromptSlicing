#include <stdio.h>
    #include <string.h>

    int main(int argc, char **argv) {
      if (argc != 2) {
        printf("Error: Incorrect arguments\n");
        return 1;
      }
      char *argument = argv[1];
      argument = strtok(argument, "\n");
      printf("%s", argument);
      return 0;
    }