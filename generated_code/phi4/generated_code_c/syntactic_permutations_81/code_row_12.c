#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    // Allocate memory for the buffer
    char *buf = (char *)malloc(BUFFER_SIZE);
    if (buf == NULL) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    // Read from standard input and store in buf
    size_t bytesRead = fread(buf, 1, BUFFER_SIZE - 1, stdin);

    if (bytesRead < 0) {
        perror("Error reading from standard input");
        free(buf);
        return EXIT_FAILURE;
    }

    // Null-terminate the buffer to safely use it as a string
    buf[bytesRead] = '\0';

    // For demonstration purposes: print what was read
    printf("Data read from stdin:\n%s\n", buf);

    // Free allocated memory
    free(buf);
    
    return EXIT_SUCCESS;
}