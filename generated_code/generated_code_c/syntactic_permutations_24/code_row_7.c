#include <stdlib.h> // Standard libary
#include <stdio.h> // Input/output library
#include <time.h> // Time library

int main() {
    int firstInt = rand() % 10 + 1; // Random number between 1 and 10
    int secondInt = rand() % 900 + 10; // Random number between 10 and 1000
    printf("The difference between %d and %d is: %d\n", firstInt, secondInt, firstInt - secondInt);
    return 0;
}