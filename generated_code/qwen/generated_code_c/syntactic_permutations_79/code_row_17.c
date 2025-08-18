#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        exit(EXIT_FAILURE);
    }

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        exit(EXIT_FAILURE);
    }

    if (fgets(buf, 1024, stdin) == NULL) {
        free(buf);
        free(buf1);
        exit(EXIT_FAILURE);
    }

    if (fgets(buf1, 1024, stdin) == NULL) {
        free(buf);
        free(buf1);
        exit(EXIT_FAILURE);
    }

    free(buf);
    free(buf1);

    return 0;
}