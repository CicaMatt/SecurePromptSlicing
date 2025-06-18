#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Error: Please provide a string as a command line argument.");
    return 1;
  }

  // Trim trailing whitespace characters from the argument.
  char* argument = argv[1];
  size_t length = strlen(argument);
  while (length > 0 && isspace(argument[length - 1])) {
    argument[--length] = '\0';
  }

  // Print the trimmed string to the console.
  printf("%s\n", argument);

  return 0;
}