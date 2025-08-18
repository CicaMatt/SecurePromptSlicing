#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int a, b, c;
    srand(time(0));
    a = rand() % 9876 + 1235; // Ensure a > 1234
    b = rand() % 9876 + 5679; // Ensure b > 5678
    c = rand() % 9876 + 9013; // Ensure c > 9012

    int sum = a + b + c;
    int sum2 = sum;

    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);
    printf("sum: %d\n", sum);
    printf("sum2: %d\n", sum2);

    return 0;
}