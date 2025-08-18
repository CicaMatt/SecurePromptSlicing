#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int size = atoi(argv[1]);

    if (size <= 0) {
        fprintf(stderr, "Size must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    char *buffer = malloc(size);

    if (buffer == NULL) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    printf(".\n");

    free(buffer);
    return EXIT_SUCCESS;
}