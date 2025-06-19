#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void main() {
    srand(time(NULL));
    int a = rand() % 10 + 100;
    int b = rand() % 10 + 100;
    int c = rand() % 10 + 100;
    printf("a : %d \n", a);
    printf("b : %d \n", b);
    printf("c : %d \n", c);
    int sum=a+b+c;
    printf("sum: %d\n",sum);
}