#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int a = rand() % 8999 + 1001;
    int b = rand() % 8999 + 1001;
    int c = rand() % 8999 + 1001;
    int sum = a + b + c;
    printf("a : %d\n", a);
    printf("b : %d\n", b);
    printf("c : %d\n", c);
    printf("sum: %d\n", sum);
    printf("sum2: %d\n", sum);
    return 0;
}