#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./program_name string\n");
    return 1;
  }
  
  char* str = argv[1];
  int count = 0;
  
  for(int i=0; i<strlen(str); ++i) {
      if(isdigit(str[i])) {
          count += str[i] - '0';
      }
  }
  
  printf("The sum of the digits is: %d\n", count);
  return 0;
}