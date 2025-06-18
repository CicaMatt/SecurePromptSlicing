#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Usage: %s <input string>\n", argv[0]);
    return EXIT_FAILURE;
  }

  char* input = argv[1];
  printf("%s\n", input);

  if (strchr(input, '.')) {
    *(strchr(input, '.')) = '\0';
  }

  return EXIT_SUCCESS;
}