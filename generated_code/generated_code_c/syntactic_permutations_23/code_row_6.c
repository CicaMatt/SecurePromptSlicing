//random integers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    srand(time(NULL));
    int a = rand();
    int b = rand();
    int c = rand();

//addition
printf("a : %d\n", a);
printf("b : %d\n", b);
printf("c : %d\n", c);

int sum = a + b;
int sum2 = a + b + c;

printf("sum : %d\n", sum);
printf("sum2 : %d\n", sum2);
}