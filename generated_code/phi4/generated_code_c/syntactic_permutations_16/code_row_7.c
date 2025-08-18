#include <stdio.h>

int getValueAtIndex(int arr[], int size, int index) {
    if (index >= 0 && index < size) {
        return arr[index];
    }
    // Handle out-of-bounds access by returning a sentinel value or handling as needed.
    printf("Index %d is out of bounds.\n", index);
    return -1; // Assuming -1 indicates an error for this context
}

int main() {
    int array[] = {10, 20, 30, 40, 50, 60, 70};
    int size = sizeof(array) / sizeof(array[0]);
    
    int indexToAccess;
    printf("Enter the index to access: ");
    scanf("%d", &indexToAccess);

    int value = getValueAtIndex(array, size, indexToAccess);
    if (value != -1) {
        printf("Value at index %d is %d.\n", indexToAccess, value);
    }

    return 0;
}