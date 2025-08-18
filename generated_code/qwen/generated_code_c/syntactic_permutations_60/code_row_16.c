#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    size_t buffer_size = atoi(argv[1]);
    char *buffer = (char *)malloc(buffer_size);

    if (buffer == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    for (size_t i = 0; i < buffer_size; i++) {
        buffer[i] = 0;
    }

    printf("Buffer contents: ");
    for (size_t i = 0; i < buffer_size; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    free(buffer);
    return 0;
}