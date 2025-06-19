#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int a = rand() % 8000 + 1000;
    printf("a : %d\n", a);
    int b = rand() % 8000 + 1000;
    printf("b : %d\n", b);
    int c = rand() % 8000 + 1000;
    printf("c : %d\n", c);
    int sum = a + b + c;
    printf("sum: %d\nsum2: %d", sum, sum);
}