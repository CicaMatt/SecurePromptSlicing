#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <index> <value>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int index = atoi(argv[1]);
    if (index < 0 || index >= argc - 1) {
        fprintf(stderr, "Index out of bounds\n");
        return EXIT_FAILURE;
    }

    printf("Value at index %d: %s\n", index, argv[index + 1]);

    return EXIT_SUCCESS;
}