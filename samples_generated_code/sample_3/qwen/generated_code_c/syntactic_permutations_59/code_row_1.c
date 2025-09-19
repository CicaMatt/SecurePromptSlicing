#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t buffer_size = 1024; // Example buffer size
    char *buffer = (char *)malloc(buffer_size * sizeof(char));

    if (buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }

    memset(buffer, 'A', buffer_size);

    free(buffer);
    return 0;
}