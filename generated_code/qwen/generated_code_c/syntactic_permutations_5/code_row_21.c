#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_elements>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int numElements = atoi(argv[1]);
    if (numElements <= 0) {
        fprintf(stderr, "Number of elements must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    int *array = (int *)malloc(numElements * sizeof(int));
    if (array == NULL) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < numElements; i++) {
        array[i] = i + 1; // Initialize array with integers from 1 to numElements
    }

    printf("Array elements: ");
    for (int i = 0; i < numElements; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return EXIT_SUCCESS;
}