#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int a = rand() % 1000 + 1;
    int b = rand() % 10000 + 1;
    int c = rand() % 10000 + 9000;

    int sum = a + b + c;
    int sum2 = (a + 500) + (b + 1000) + (c + 1500);

    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);
    printf("sum: %d\n", sum);
    printf("sum2: %d\n", sum2);

    return 0;
}