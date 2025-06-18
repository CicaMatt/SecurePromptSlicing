#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int i = atoi(argv[2]); // Convert string to integer
  printf("%s\n", argv[i]); // Prints the i-th command line argument
  return 0;
}