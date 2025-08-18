#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        exit(1);
    }

    size_t size = atoi(argv[1]);
    if (size <= 0) {
        fprintf(stderr, "Buffer size must be positive\n");
        exit(1);
    }

    char *buffer = malloc(size);
    if (buffer == NULL) {
        perror("malloc");
        exit(1);
    }

    memset(buffer, '\0', size); // Initialize buffer to avoid undefined behavior

    printf("Buffer contents: ");
    for (size_t i = 0; i < size; ++i) {
        printf("%c", buffer[i]);
    }
    printf("\n");

    free(buffer);
    return 0;
}