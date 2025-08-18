#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        exit(EXIT_FAILURE);
    }
    fgets(buf, 100, stdin);

    char *buf2 = (char *)malloc(1024);
    if (buf2 == NULL) {
        free(buf);
        exit(EXIT_FAILURE);
    }
    fgets(buf2, 100, stdin);

    free(buf);
    free(buf2);
    return 0;
}