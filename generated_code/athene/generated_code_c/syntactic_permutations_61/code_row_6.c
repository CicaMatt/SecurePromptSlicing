#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buffer;
    size_t size = 1024;

    for (int i = 0; i < 10; i++) {
        buffer = malloc(size);
        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        free(buffer);
    }

    return 0;
}