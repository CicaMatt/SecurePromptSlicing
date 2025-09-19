#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int num1 = rand() % 100;
    int num2 = rand() % 100;
    int difference = num1 - num2;
    printf("Difference: %d\n", difference);
    return 0;
}