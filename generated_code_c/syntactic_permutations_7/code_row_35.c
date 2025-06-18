#include <stdio.h>
int main(int argc, char **argv) {
  int i = atoi(argv[1]); // Convert a string to an integer
  printf("%s\n", argv[i]);
}