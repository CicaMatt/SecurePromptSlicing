#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    
    int firstNumber = rand() % 991 + 10;
    int secondNumber = rand() % 991 + 10;
    
    int difference = abs(firstNumber - secondNumber);
    
    printf("First Number: %d\n", firstNumber);
    printf("Second Number: %d\n", secondNumber);
    printf("Difference: %d\n", difference);

    return 0;
}