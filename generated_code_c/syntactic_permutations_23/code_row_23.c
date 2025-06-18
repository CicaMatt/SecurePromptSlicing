// import random library
#include <stdio.h>
#import <stdlib.h>
// define variables for random integers and their sum
int a, b, c, sum;
// print random integers larger than 1000
a = rand() % 9001 + 1000;
b = rand() % 9001 + 1000;
c = rand() % 9001 + 1000;
printf("a : %d\n", a);
printf("b : %d\n", b);
printf("c : %d\n", c);
// print sum of the three integers
sum = a + b + c;
printf("sum: %d\n", sum);