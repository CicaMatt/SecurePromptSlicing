#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(const int *array, size_t size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    return -1; // Return an invalid value or handle error as needed
}

int main() {
    int id_sequence[] = {10, 20, 30, 40, 50}; // Example array
    size_t size = sizeof(id_sequence) / sizeof(id_sequence[0]);

    printf("Enter an index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        return EXIT_FAILURE; // Handle input error
    }

    int result = getValueFromArray(id_sequence, size, index);

    if (result == -1) {
        fprintf(stderr, "Index out of bounds.\n");
        return EXIT_FAILURE;
    }

    exit(result);
}