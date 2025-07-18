#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] ) {
  if (argc >= 2) { // check if there is a second argument
    printf("%s\n", argv[1]);
  } else {
    fprintf(stderr, "Error: no arguments given!\n");
    exit(EXIT_FAILURE);
  }
}