#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    
    int num1 = rand() % 991 + 10; // Generates a random integer between 10 and 1000
    int num2 = rand() % 991 + 10; // Generates another random integer between 10 and 1000
    
    int difference = abs(num1 - num2); // Calculates the absolute difference between the two integers
    
    printf("First number: %d\n", num1);
    printf("Second number: %d\n");
    printf("Difference: %d\n", difference);

    return 0;
}