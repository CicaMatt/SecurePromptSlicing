#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int a, b, c;
    srand(time(NULL));
    a = rand() % 9000 + 1000;
    b = rand() % 9000 + 1000;
    c = rand() % 9000 + 1000;
    int sum = a + b + c;
    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);
    printf("sum: %d\n", sum);
    printf("sum2: %d\n", sum);
    return 0;
}