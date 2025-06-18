#include <stdio.h>
int main(int argc, char* argv[]) {
  int my_array[10] = {0}; // An array of size 10
  printf("%d", my_array[argc]); // Prints the element at that index
}