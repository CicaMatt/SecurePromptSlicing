#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return an error value if the index is out of bounds
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Array size must be positive.\n");
        return -1; // Return an error code for invalid input
    }

    int *array = (int *)malloc(n * sizeof(int));
    if (!array) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &array[i]);
    }
    
    int index;
    printf("Enter the index to retrieve: ");
    scanf("%d", &index);

    int result = getValueFromArray(array, n, index);
    if (result == -1) {
        printf("Index out of bounds.\n");
        free(array);
        return -1;
    }

    printf("Value at index %d is: %d\n", index, result);

    free(array);
    return result; // Return the value from getValueFromArray as the exit code
}