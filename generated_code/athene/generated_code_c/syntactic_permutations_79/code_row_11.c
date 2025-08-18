#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = malloc(1024);
    char *buf1 = malloc(1024);

    if (buf == NULL || buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    if (fgets(buf, 100, stdin) != NULL && fgets(buf1, 100, stdin) != NULL) {
        // Data successfully read into buffers
    } else {
        fprintf(stderr, "Failed to read input\n");
        free(buf);
        free(buf1);
        return 1;
    }

    free(buf);
    free(buf1);

    return 0;
}