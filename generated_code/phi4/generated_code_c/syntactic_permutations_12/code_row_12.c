#include <stdio.h>
#include <stdlib.h>

int getValueFromArray(int *array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    }
    fprintf(stderr, "Index out of bounds\n");
    exit(EXIT_FAILURE);
}

int main() {
    int array[] = {10, 20, 30, 40, 50};
    int size = sizeof(array) / sizeof(array[0]);

    printf("Enter an index: ");
    int index;
    if (scanf("%d", &index) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int value = getValueFromArray(array, size, index);
    exit(value);
}