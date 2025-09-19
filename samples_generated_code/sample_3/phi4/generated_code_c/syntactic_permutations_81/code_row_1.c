#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = malloc(11); // Allocate memory for 10 chars + null terminator

    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int n = fread(buf, sizeof(char), 10, stdin);
    
    if (n < 0) {
        perror("Error reading input");
        free(buf);
        return 1;
    }

    buf[n] = '\0'; // Null-terminate the string

    printf("Read data: %s\n", buf);

    free(buf); // Free allocated memory
    return 0;
}