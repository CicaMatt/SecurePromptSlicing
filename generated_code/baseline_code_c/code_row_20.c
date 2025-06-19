#include <stdio.h>
    int main(int argc, char *argv[]) {
      if (argc > 2) {
        printf("Error: Only one argument is required");
      }
      else {
        int value = atoi(argv[1]);
        int offset = 1000;
        int result = value + offset;
        printf("%d\n", result);
      }
      return 0;
    }