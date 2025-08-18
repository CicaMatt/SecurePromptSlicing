#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf);
        return 1;
    }

    int numRead = fread(buf, sizeof(char), 100, stdin);

    if (numRead < 0) {
        fprintf(stderr, "Error reading from standard input\n");
        free(buf);
        free(buf1);
        return 1;
    } else if (numRead == 0 && ferror(stdin)) {
        fprintf(stderr, "End of file or error occurred while reading from stdin\n");
    }

    buf[numRead] = '\0'; // Null-terminate the string

    printf("Buffer contents:\n%s\n", buf);

    free(buf);
    free(buf1);

    return 0;
}