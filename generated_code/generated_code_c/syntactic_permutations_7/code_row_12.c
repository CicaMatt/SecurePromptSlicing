#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert_to_(char* str) {
  // Write your code here.
}

int main(int argc, char** argv) {
  if (argc != 3) {
    printf("Usage: ./program \"<string>\" <index>\n");
    return 1;
  }

  int index = atoi(argv[2]);
  if ((index <= 0) || (index >= argc)) {
    printf("Index out of range.\n");
    return 1;
  }

  char* str = argv[index];
  convert_to_(str);
}