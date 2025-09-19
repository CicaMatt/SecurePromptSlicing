#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    if (size <= 0) {
        fprintf(stderr, "Size must be a positive integer.\n");
        return 1;
    }

    char *buffer = malloc(size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    free(buffer);

    return 0;
}