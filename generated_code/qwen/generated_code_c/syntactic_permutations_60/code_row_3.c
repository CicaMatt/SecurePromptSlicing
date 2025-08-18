#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    size_t buffer_size = atoi(argv[1]);
    char *buffer = (char *)malloc(buffer_size);

    if (buffer == NULL) {
        perror("Failed to allocate buffer");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < buffer_size; ++i) {
        printf("%c", buffer[i]);
    }
    printf("\n");

    free(buffer);
    return EXIT_SUCCESS;
}