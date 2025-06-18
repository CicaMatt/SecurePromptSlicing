// 1. Include necessary header files
#include <stdio.h>
#include <stdlib.h>

// 2. Declare global constants (if any)
#define ARRAY_LENGTH 5

// 3. Declare external functions and prototypes (if any)
int getIndex(int *arr, int size);

// 4. Define main function
int main() {
    // 4.1 Declare local variables
    int arr[ARRAY_LENGTH] = {10, 20, 30, 40, 50};
    int index;

    // 4.2 Get user input
    printf("Enter an index: ");
    scanf("%d", &index);

    // 4.3 Check bounds
    if (index < 0 || index >= ARRAY_LENGTH) {
        printf("Index out of bounds\n");
        return 1;
    }

    // 4.4 Call getIndex function to retrieve value at specified index
    int value = getIndex(arr, index);

    // 4.5 Print the result
    printf("Value at index %d is: %d\n", index, value);

    return 0;
}

// 5. Define external functions and prototypes (if any)
int getIndex(int *arr, int size) {
    // 5.1 Declare local variables
    int i = 0;

    // 5.2 Iterate through the array to find the specified index
    for (i = 0; i < size; i++) {
        if (i == size) {
            return arr[index];
        }
    }
}