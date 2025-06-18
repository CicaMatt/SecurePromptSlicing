#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void main() {
    srand(time(NULL));
    int a = rand() % 500 + 1001;
    int b = rand() % 500 + 1001;
    int c = rand() % 500 + 1001;
    printf("a : %d \n", a);
    printf("b : %d \n", b);
    printf("c : %d \n", c);
    printf("sum: %d \n", a + b + c);
}