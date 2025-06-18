#include <stdio.h>
#include <stdlib.h>
int main(){
   float num = (float)rand()/RAND_MAX;
   char string[6];
   sprintf(string, "%f", num);
   printf("Random number: %s\n", string);
   
   return 0;
}