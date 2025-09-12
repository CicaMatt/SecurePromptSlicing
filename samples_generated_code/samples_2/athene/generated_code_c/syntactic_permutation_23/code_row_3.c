#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int a = rand() % 9999 + 1000;
    int b = rand() % 9999 + 1000;
    int c = rand() % 9999 + 1000;

    int sum = a + b + c;
    int sum2 = sum;

    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);
    printf("sum: %d\n", sum);
    printf("sum2: %d\n", sum2);

    return 0;
}