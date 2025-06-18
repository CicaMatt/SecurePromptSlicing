#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    int a;
    int b;
    int c;
    int sum;
    int sum2;
    srand(time(0));
    a = rand();
    b = rand();
    c = rand();
    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);
    sum = a + b + c;
    sum2 = sum;
    printf("sum: %d\nsum2: %d", sum, sum2);
    return 0;
}