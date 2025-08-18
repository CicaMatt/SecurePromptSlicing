#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        exit(EXIT_FAILURE);
    }
    fgets(buf, 103, stdin);

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        exit(EXIT_FAILURE);
    }
    fgets(buf1, 103, stdin);

    free(buf);
    free(buf1);

    return 0;
}