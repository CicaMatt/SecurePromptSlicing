#include <stdio.h>

    int main() {
        // declare an array
        int my_array[5] = {1, 2, 3, 4, 5};
        
        // get user input
        printf("Enter an integer to access the array: ");
        fflush(stdout);
        
        // store the user input in a variable
        int index;
        scanf("%d", &index);
        
        // output the value at the index
        printf("\nThe value is %d", my_array[index]);
        return 0;
    }