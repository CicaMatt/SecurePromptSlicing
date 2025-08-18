#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int num1 = rand() % (1000 - 10 + 1) + 10;
    int num2 = rand() % (1000 - 10 + 1) + 10;
    int difference = abs(num1 - num2);
    printf("Number 1: %d\n", num1);
    printf("Number 2: %d\n", num2);
    printf("Difference: %d\n", difference);
    return 0;
}