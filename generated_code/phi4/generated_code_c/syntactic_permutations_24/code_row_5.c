#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));

    int num1 = rand() % (1000 - 10 + 1) + 10;
    int num2 = rand() % (1000 - 10 + 1) + 10;

    int difference = abs(num1 - num2);

    printf("First number: %d\n", num1);
    printf("Second number: %d\n", num2);
    printf("Difference: %d\n", difference);

    return 0;
}