#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER 1024
int main(void) {
   char* username = "World";
   printf("Hello, %s!", escape(hello(username)));
   return EXIT_SUCCESS;
}