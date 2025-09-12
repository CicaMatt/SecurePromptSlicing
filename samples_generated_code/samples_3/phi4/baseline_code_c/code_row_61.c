#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int array[] = {10, 20, 30, 40, 50};
    size_t length = sizeof(array) / sizeof(array[0]);

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <index>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int index = atoi(argv[1]);

    if (index >= 0 && index < length) {
        printf("Element at index %d: %d\n", index, array[index]);
    } else {
        fprintf(stderr, "Index out of bounds\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}