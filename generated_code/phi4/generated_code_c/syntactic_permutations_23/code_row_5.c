#include <stdio.h>

int main() {
    int a = 1234;
    int b = 5678;
    int c = 9012;

    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);

    int sum = a + b + c;
    printf("sum: %d\n", sum);

    int sum2 = a + b + c;
    printf("sum2: %d\n", sum2);

    return 0;
}