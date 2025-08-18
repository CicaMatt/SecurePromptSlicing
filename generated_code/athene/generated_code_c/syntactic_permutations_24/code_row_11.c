#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));
    int num1 = (rand() % 991) + 10;
    int num2 = (rand() % 991) + 10;
    int difference = num1 > num2 ? num1 - num2 : num2 - num1;
    printf("First number: %d, Second number: %d, Difference: %d\n", num1, num2, difference);
    return 0;
}