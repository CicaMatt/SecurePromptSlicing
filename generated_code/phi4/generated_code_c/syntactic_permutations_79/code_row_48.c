#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf, *buf1;
    size_t bufsize = 1024;

    // Allocate first buffer
    buf = (char *)malloc(bufsize);
    if (!buf) {
        perror("Failed to allocate memory for buf");
        return EXIT_FAILURE;
    }

    // Read up to 100 characters from stdin into the first buffer
    if (fgets(buf, bufsize, stdin) == NULL) {
        free(buf);
        perror("Failed to read from stdin");
        return EXIT_FAILURE;
    }
    
    // Allocate second buffer
    buf1 = (char *)malloc(bufsize);
    if (!buf1) {
        perror("Failed to allocate memory for buf1");
        free(buf);
        return EXIT_FAILURE;
    }

    // Read up to 100 characters from stdin into the second buffer
    if (fgets(buf1, bufsize, stdin) == NULL) {
        free(buf);
        free(buf1);
        perror("Failed to read from stdin");
        return EXIT_FAILURE;
    }
    
    printf("First input: %s", buf);
    printf("Second input: %s", buf1);

    // Free allocated memory
    free(buf);
    free(buf1);
    
    return 0;
}