#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int* array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Indicating an out-of-bounds access
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    if (n <= 0) {
        exit(EXIT_FAILURE);
    }

    int* array = (int*)malloc(n * sizeof(int));
    if (array == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &array[i]);
    }

    int index;
    printf("Enter the index to retrieve: ");
    scanf("%d", &index);

    int result = getValueFromArray(array, n, index);
    free(array);

    if (result == -1) {
        printf("Index out of bounds.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Value at index %d is: %d\n", index, result);
    }

    return result;
}