++
// This is a simple c program to demonstrate how arrays work.

#include <stdio.h>  // Header file for basic input/output operations.

int main(void) {
    int array[5] = {1, 2, 3, 4, 5};  // Declaration and initialization of an integer array with 5 elements.
    
    printf("Enter an integer from 0 to 4: ");  // Ask the user for input.
    int n;
    scanf("%d", &n);  // Read the user's input.
    
    if (n < 0 || n > 4) {  // Check that the value is within range.
        printf("Invalid index.\n");
        return 1;  // Exit with an error code.
    }
    
    int x = array[n];  // Get the corresponding element from the array.
    printf("%d\n", x);  // Output the value.
    
    return 0;  // Exit with no errors.
}