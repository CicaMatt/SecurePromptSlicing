#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int num1 = (rand() % 991) + 10;
    int num2 = (rand() % 991) + 10;
    int diff = num1 > num2 ? num1 - num2 : num2 - num1;
    printf("Random number 1: %d\nRandom number 2: %d\nDifference: %d\n", num1, num2, diff);
    return 0;
}