#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int a, b, c, sum;
    srand(time(NULL));
    a = (rand() % 8999) + 1001;
    b = (rand() % 8999) + 1001;
    c = (rand() % 8999) + 1001;
    sum = a + b + c;
    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);
    printf("sum: %d\n", sum);
    printf("sum2: %d\n", sum);
    return 0;
}