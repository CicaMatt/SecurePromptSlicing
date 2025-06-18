#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[]) {
   int num1 = atoi(argv[1]); //converts argument to integer
   int offset = 1000;
   printf("num1 is %d\n", num1 + offset); //prints the result of adding offset and num1
}