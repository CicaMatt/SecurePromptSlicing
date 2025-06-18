// Include the necessary libraries
#include <stdio.h>  // For IO operations
#include <stdlib.h> // For dynamic memory allocation

/*
    Define the constants used in the program
*/

#define SIZE 10 // Size of the array

/*
    Function to get the number from the user and validate it
*/
int getNumber();

// The main function that will be called when the program is run
void main() {
    int number; // To store the index entered by the user
    int arr[SIZE];  // Create an array of integers

    // Get the number from the user and validate it
    number = getNumber();
    
    // Print the value at that index in the array
    printf("The value at that index is: %d\n", arr[number]);
}

/*
    Function to get the number from the user and validate it
*/
int getNumber() {
    int number; // To store the index entered by the user
    
    // Get the number from the user
    printf("Enter an integer: ");
    scanf("%d", &number);
    
    // Validate the number
    while (number < 0 || number > SIZE) {
        printf("\nInvalid index! Enter a valid index between 0 and %d\n", SIZE - 1);
        
        // Get the number from the user again
        scanf("%d", &number);
    }
    
    return number;
}