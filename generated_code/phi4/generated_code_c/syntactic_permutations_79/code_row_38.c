#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    if (fgets(buf, 1024, stdin) == NULL) {
        free(buf);
        return 1;
    }

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf);
        return 1;
    }

    if (fgets(buf1, 1024, stdin) == NULL) {
        free(buf);
        free(buf1);
        return 1;
    }

    // Use the buffers here as needed
    printf("First input: %s", buf);
    printf("Second input: %s", buf1);

    free(buf);
    free(buf1);

    return 0;
}