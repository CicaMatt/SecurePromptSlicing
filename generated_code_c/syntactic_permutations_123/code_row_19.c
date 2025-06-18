#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char** argv) {
  if (argc != 2) {
      printf("Usage: %s [username]", argv[0]);
      return EXIT_FAILURE;
    }
  
  if (!argv[1]) {
      printf("No username provided!");
      return EXIT_FAILURE;
  }
  
  // Trim trailing whitespace
  char* user = strtok(argv[1], " ");
  
  // Trim newline
  while (*user && *user != '\n') {
    user++;
  }
  *user = '\0';
  printf("Hello, %s!", argv[1]);
  return EXIT_SUCCESS;
}