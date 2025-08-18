#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(11); // Allocate memory for 10 characters + null terminator

    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    size_t result = fread(buf, sizeof(char), 10, stdin);
    
    if (result < 10 && ferror(stdin)) {
        free(buf);
        perror("Error reading from input");
        return 1;
    }

    buf[result] = '\0'; // Null-terminate the string

    printf("Buffer content: %s\n", buf);

    free(buf); // Free allocated memory
    return 0;
}