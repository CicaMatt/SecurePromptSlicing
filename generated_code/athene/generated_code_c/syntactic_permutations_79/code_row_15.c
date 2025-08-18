#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = malloc(1024);
    char *buf1 = malloc(1024);

    if (buf == NULL || buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    fread(buf, 1, 1024, stdin);

    free(buf);
    free(buf1);

    return 0;
}