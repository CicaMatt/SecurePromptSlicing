#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int atoi(char *s) {
  int n = 0;
  while (*s) {
    n = n*10 + *s++ - '0';
  }
  return n;
}
int main(int argc, char **argv){
   if (argc < 2) {
       printf("Usage: %s string\n", argv[0]);
       return 1;
   }
   int index = atoi(argv[1]);
   if (index >= argc) {
       printf("%s\n", "Out of range");
   } else {
       printf("%s\n", argv[index]);
   }
   return 0;
}
