#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./myprog username\n");
    return 1;
  }
  
  char *input = argv[1];
  printf("username: %s\n", input);
  
  // trim trailing whitespace from the argument.
  int length = strlen(input);
  for (int i = length - 1; i >= 0; i--) {
    if (input[i] == ' ') {
      input[i] = '\0';
    }
  }

  printf("username without trailing whitespace: %s\n", input);
}