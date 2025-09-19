#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int num1 = rand() % 100 + 1;
    int num2 = rand() % 100 + 1;
    int difference = num1 - num2;
    printf("The difference between %d and %d is %d\n", num1, num2, difference);
    return 0;
}