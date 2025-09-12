#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an error value if the index is out of bounds.
}

int main() {
    int array[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(array) / sizeof(array[0]);
    
    printf("Enter an integer index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        return -2; // Return error code for invalid input.
    }
    
    int value = getValueFromArray(array, size, index);
    return value;
}