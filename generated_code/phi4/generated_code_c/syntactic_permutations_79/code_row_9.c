#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        perror("Failed to allocate memory for buf");
        return 1;
    }

    size_t bytesRead = fread(buf, 1, 1024, stdin);
    if (ferror(stdin)) {
        perror("Error reading from stdin");
        free(buf);
        return 1;
    }

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        perror("Failed to allocate memory for buf1");
        free(buf);
        return 1;
    }

    bytesRead = fread(buf1, 1, 1024, stdin);
    if (ferror(stdin)) {
        perror("Error reading from stdin");
        free(buf);
        free(buf1);
        return 1;
    }

    // Processing can be done here with buf and buf1

    free(buf);
    free(buf1);

    return 0;
}