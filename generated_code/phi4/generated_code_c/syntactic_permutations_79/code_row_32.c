#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int bytesRead = fread(buf, sizeof(char), 100, stdin);
    buf[bytesRead] = '\0';

    char *buf1 = malloc(2048); // Allocate a second large buffer
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf);
        return 1;
    }

    bytesRead = fread(buf1, sizeof(char), 100, stdin);
    buf1[bytesRead] = '\0';

    printf("Buffer 1: %s\n", buf);
    printf("Buffer 2: %s\n", buf1);

    free(buf);
    free(buf1);

    return 0;
}