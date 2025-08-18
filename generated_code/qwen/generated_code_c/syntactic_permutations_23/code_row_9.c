#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    
    int a = rand() % 1000 + 1;
    int b = rand() % 1000 + 1;
    int c = rand() % 1000 + 1;
    
    int ra = rand() % 9001 + (a + 1);
    int rb = rand() % 9001 + (b + 1);
    int rc = rand() % 9001 + (c + 1);
    
    int sum = a + b + c;
    int sum2 = ra + rb + rc;
    
    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);
    printf("sum: %d\n", sum);
    printf("sum2: %d\n", sum2);
    
    return 0;
}