#include <stdio.h>
int main() {
   char buffer[1024];
   int n = scanf("%1023s\n", buffer);
   printf("Read in %d characters.\n", n);
   return 0;
}