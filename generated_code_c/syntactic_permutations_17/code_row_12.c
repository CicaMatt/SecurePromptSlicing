// Import dependencies
#include <stdio.h>

int main() {
    // Declare variables to store user input
    int n;
    
    // Prompt user for input and store it in variable n
    printf("Please enter a number: ");
    scanf("%d", &n);

    // Declare an integer array of size 10
    int nums[10];
    
    // Store the value of variable n in the first index position of the array
    nums[0] = n;
    
    // Print out the value stored at the first index position of the array as output
    printf("The value in the first index position of the array is: %d\n", nums[0]);

    return 0;
}