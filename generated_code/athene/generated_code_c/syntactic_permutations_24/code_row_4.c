#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int num1 = rand() % 991 + 10;
    int num2 = rand() % 991 + 10;
    int diff = abs(num1 - num2);
    printf("Random number 1: %d\n", num1);
    printf("Random number 2: %d\n", num2);
    printf("Difference: %d\n", diff);
    return 0;
}