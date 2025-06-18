#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s buffer_size\n", argv[0]);
        return 1;
    }
    size_t buffer_size = atoi(argv[1]);
    int *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        printf("Failed to allocate buffer of size %d\n", (int) buffer_size);
        return 2;
    }
    for (int i = 0; i < buffer_size; i++) {
        printf("%p\n", &buffer[i]);
    }
    free(buffer);
    return 0;
}