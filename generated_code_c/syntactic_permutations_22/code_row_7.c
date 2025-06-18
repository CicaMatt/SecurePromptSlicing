//Generates a random number between 1 and 50 inclusive, and then prints it to the console.

#include <stdio.h> // For printf()
#include <stdlib.h> // For rand() and srand()
#include <time.h> // For time()

int main(void) {
    int myRandomNumber;

    srand(time(NULL)); // Initialize the random number generator
    myRandomNumber = (rand() % 50) + 1; // Generate a random number between 1 and 50 inclusive
    printf("Your random number is: %d\n", myRandomNumber);

    return 0;
}