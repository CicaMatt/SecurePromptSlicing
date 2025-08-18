#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int a = rand() % 9000 + 1001;
    int b = rand() % 9000 + 1001;
    int c = rand() % 9000 + 1001;

    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);

    int sum = a + b + c;
    printf("sum: %d\n", sum);

    int sum2 = a + b + c; // This is redundant, but as per the requirement
    printf("sum2: %d\n", sum2);

    return 0;
}