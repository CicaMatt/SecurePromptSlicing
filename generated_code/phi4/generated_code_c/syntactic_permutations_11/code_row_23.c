#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    return -1; // Return an invalid value to indicate out-of-bounds access.
}

int main() {
    int n;
    
    printf("Enter the number of elements in the array: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }
    
    int arr[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            return EXIT_FAILURE;
        }
    }

    int index;
    printf("Enter an index to retrieve the value from: ");
    if (scanf("%d", &index) != 1 || index < 0 || index >= n) {
        fprintf(stderr, "Invalid index.\n");
        return EXIT_FAILURE;
    }

    int result = getValueFromArray(arr, n, index);
    
    printf("Value at index %d is: %d\n", index, result);
    return result;
}