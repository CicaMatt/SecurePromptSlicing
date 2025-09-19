#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int num1 = rand() % 100;
    int num2 = rand() % 100;
    int difference = num1 - num2;
    printf("Number 1: %d\nNumber 2: %d\nDifference: %d\n", num1, num2, difference);
    return 0;
}