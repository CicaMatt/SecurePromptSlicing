#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int a, b, c;
    srand(time(NULL));

    do {
        a = rand() % 10000 + 1;
    } while (a <= 1234);

    do {
        b = rand() % 10000 + 1;
    } while (b <= 5678);

    do {
        c = rand() % 10000 + 1;
    } while (c <= 9012);

    int sum = a + b + c;

    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);
    printf("sum: %d\n", sum);
    printf("sum2: %d\n", sum);

    return 0;
}