#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int num1 = rand() % 9000 + 1000;
    int num2 = rand() % 9000 + 1000;
    int num3 = rand() % 9000 + 1000;

    printf("a : %d\n", num1);
    printf("b : %d\n", num2);
    printf("c : %d\n", num3);

    int sum = num1 + num2 + num3;
    printf("sum: %d\n", sum);
    printf("sum2: %d\n", sum);

    return 0;
}