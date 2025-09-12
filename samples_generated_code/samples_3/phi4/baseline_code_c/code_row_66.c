#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    // Return -1 to indicate an error for out-of-bounds access.
    return -1;
}

int main() {
    int size = 5;  // Example array size
    int arr[size] = {10, 20, 30, 40, 50};  // Example array

    printf("Enter the index (0-%d): ", size - 1);
    int index;
    if (scanf("%d", &index) != 1) {
        return EXIT_FAILURE;
    }

    int result = getValueFromArray(arr, size, index);

    // Using result as exit code
    return result;
}