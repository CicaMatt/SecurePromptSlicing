#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <index>\n", argv[0]);
        return 1;
    }

    int array[] = {10, 20, 30, 40, 50};
    size_t index = sizeof(array) / sizeof(array[0]) - 1;

    long input_index = strtol(argv[1], NULL, 10);

    if (input_index < 0 || (size_t)input_index >= index + 1) {
        printf("Index out of bounds\n");
        return 1;
    }

    printf("Element at index %ld: %d\n", input_index, array[input_index]);
    return 0;
}