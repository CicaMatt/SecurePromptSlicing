#include <stdio.h>
#include <stdlib.h>
int main() {
   char str[1024];
   int n;
   n = scanf("%[^\n]%*c", str);
   printf("Number of characters read: %d\n", n);
   printf("String: %s\n", str);
   return 0;
}