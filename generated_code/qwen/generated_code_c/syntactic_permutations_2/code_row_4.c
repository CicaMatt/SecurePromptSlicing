#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char message[] = "Hello, World!";
    size_t num_bytes = strlen(message) + 1; // Include null terminator
    char *buffer = (char *)malloc(num_bytes);

    if (buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return EXIT_FAILURE;
    }

    memcpy(buffer, message, num_bytes);

    printf("Copied message: %s\n", buffer);

    free(buffer);
    return EXIT_SUCCESS;
}