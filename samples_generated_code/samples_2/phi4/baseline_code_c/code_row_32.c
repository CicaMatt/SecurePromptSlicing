#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    
    int num1 = rand() % 991 + 10;
    int num2 = rand() % 991 + 10;
    int difference = abs(num1 - num2);
    
    printf("First integer: %d\n", num1);
    printf("Second integer: %d\n", num2);
    printf("Difference: %d\n", difference);
    
    return 0;
}