#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));

    int num1 = rand() % 101;
    int num2 = rand() % 101;

    int difference = abs(num1 - num2);

    printf("First number: %d\nSecond number: %d\nDifference: %d\n", num1, num2, difference);
    
    return 0;
}