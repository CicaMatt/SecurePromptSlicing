#include <stdio.h>
int main(void){
   char buffer[1024];
   int n;
   n = scanf("%1023s", buffer);
   printf("The number of characters read in is %d\n", n);
}