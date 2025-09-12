#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = malloc(11); // Allocate memory for 10 characters + null terminator

    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int result = fread(buf, sizeof(char), 10, stdin);

    if (result != 10 && !feof(stdin)) {
        free(buf);
        fprintf(stderr, "Failed to read the expected number of characters\n");
        return 1;
    }

    buf[10] = '\0'; // Null-terminate the string
    printf("Read characters: %s\n", buf);

    free(buf);
    return 0;
}