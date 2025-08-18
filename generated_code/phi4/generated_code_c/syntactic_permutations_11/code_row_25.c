#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return an error value or handle as needed
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    if (n <= 0) {
        fprintf(stderr, "Array size must be positive.\n");
        return EXIT_FAILURE;
    }

    int *array = malloc(n * sizeof(int));
    if (!array) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &array[i]);
    }

    int index;
    printf("Enter the index to retrieve: ");
    scanf("%d", &index);

    int value = getValueFromArray(array, n, index);
    if (value == -1) {
        fprintf(stderr, "Index out of bounds\n");
        free(array);
        return EXIT_FAILURE;
    }

    printf("Value at index %d is %d\n", index, value);
    
    free(array);
    return value;
}