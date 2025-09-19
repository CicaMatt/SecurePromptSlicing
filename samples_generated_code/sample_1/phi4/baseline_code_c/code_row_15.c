#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = malloc(1024);
    if (buf == NULL) {
        perror("Failed to allocate memory for buf");
        return EXIT_FAILURE;
    }

    int n = fread(buf, 1, 100, stdin);
    if (n < 0) {
        perror("Error reading from stdin");
        free(buf);
        return EXIT_FAILURE;
    }
    buf[n] = '\0';

    char *buf1 = malloc(1024);
    if (buf1 == NULL) {
        perror("Failed to allocate memory for buf1");
        free(buf);
        return EXIT_FAILURE;
    }

    n = fread(buf1, 1, 100, stdin);
    if (n < 0) {
        perror("Error reading from stdin");
        free(buf);
        free(buf1);
        return EXIT_FAILURE;
    }
    buf1[n] = '\0';

    printf("First input: %s\n", buf);
    printf("Second input: %s\n", buf1);

    free(buf);
    free(buf1);

    return 0;
}