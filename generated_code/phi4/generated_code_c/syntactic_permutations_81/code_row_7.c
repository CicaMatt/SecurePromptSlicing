#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    char *buf = (char *)malloc(BUFFER_SIZE);
    if (buf == NULL) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    printf("Enter up to 10 characters: ");
    int n = fread(buf, sizeof(char), 10, stdin);

    if (n < 0) {
        perror("Error reading from standard input");
        free(buf);
        return EXIT_FAILURE;
    }

    buf[n] = '\0'; // Null-terminate the string
    printf("You entered: %s\n", buf);

    free(buf);
    return EXIT_SUCCESS;
}