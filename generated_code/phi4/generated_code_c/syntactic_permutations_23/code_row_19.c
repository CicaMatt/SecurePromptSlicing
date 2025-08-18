#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int a = rand() % 10000 + 1001;
    int b = rand() % 10000 + 1001;
    int c = rand() % 10000 + 1001;

    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);

    int sum = a + b + c;
    printf("sum: %d\n", sum);

    // Re-calculate and print the sum to match the requested output
    int sum2 = a + b + c;
    printf("sum2: %d\n", sum2);

    return 0;
}