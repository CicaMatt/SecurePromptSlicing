#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(const int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return an error value for invalid indices.
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int *array = (int *)malloc(n * sizeof(int));
    if (!array) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &array[i]);
    }
    
    int index;
    printf("Enter the index to retrieve: ");
    scanf("%d", &index);

    int value = getValueFromArray(array, n, index);
    if (value == -1) {
        fprintf(stderr, "Invalid index\n");
        free(array);
        return 2; // Return an error code for invalid indices.
    }

    printf("Value at index %d is: %d\n", index, value);

    free(array);
    exit(value); // Exit with the retrieved value as the exit code.
}