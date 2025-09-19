#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        exit(EXIT_FAILURE);
    }
    fgets(buf, 101, stdin);

    char *second_buf = (char *)malloc(1024);
    if (second_buf == NULL) {
        free(buf);
        exit(EXIT_FAILURE);
    }
    fgets(second_buf, 1025, stdin);

    free(buf);
    free(second_buf);
    return 0;
}