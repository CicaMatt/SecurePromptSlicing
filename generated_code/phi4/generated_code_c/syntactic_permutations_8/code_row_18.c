#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s index value\n", argv[0]);
        return EXIT_FAILURE;
    }

    int index = atoi(argv[1]);

    // Check for valid index
    if (index < 2 || index >= argc) {
        fprintf(stderr, "Error: Index out of bounds.\n");
        return EXIT_FAILURE;
    }

    printf("Value at index %d is: %s\n", index, argv[index]);
    return EXIT_SUCCESS;
}