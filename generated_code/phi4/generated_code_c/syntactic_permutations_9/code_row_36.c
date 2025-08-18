#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s index\n", argv[0]);
        return EXIT_FAILURE;
    }

    int index = atoi(argv[1]);

    if (index < 0 || index >= argc) {
        fprintf(stderr, "Error: Index out of bounds. Please provide an index between 0 and %d.\n", argc - 1);
        return EXIT_FAILURE;
    }

    printf("%s\n", argv[index + 1]);
    return EXIT_SUCCESS;
}