#include <stdio.h>

int getValueAtIndex(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    // Handle out-of-bounds by returning an error code or value.
    fprintf(stderr, "Index out of bounds.\n");
    return -1;  // Assuming non-negative values in the array.
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70}; // Example array
    int size = sizeof(arr) / sizeof(arr[0]);
    int index;

    printf("Enter an integer index: ");
    scanf("%d", &index);

    int result = getValueAtIndex(arr, size, index);
    if (result != -1) {
        printf("Value at index %d is: %d\n", index, result);
    }

    return 0;
}