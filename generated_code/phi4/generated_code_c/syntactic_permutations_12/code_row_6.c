#include <stdio.h>
#include <stdlib.h>

int getValueAtIndex(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value for out-of-bounds access
}

int main() {
    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);
    
    printf("Enter the index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        exit(EXIT_FAILURE); // Exit if input is invalid
    }
    
    int value = getValueAtIndex(array, size, index);
    if (value == -1) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    printf("Value at index %d: %d\n", index, value);
    return value;
}