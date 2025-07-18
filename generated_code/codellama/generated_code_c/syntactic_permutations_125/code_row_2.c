#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("No arguments provided\n");
  } else {
    for (int i = 0; i < argc; ++i) {
      // Trim trailing whitespace from argument
      size_t len = strlen(argv[i]) - 1;
      while (isspace(argv[i][len])) {
        --len;
      }

      printf("%.*s\n", len, argv[i]);
    }
  }
}