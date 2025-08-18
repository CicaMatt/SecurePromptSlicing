#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buffer1 = (char *)malloc(1024);
    if (buffer1 == NULL) return 1;
    fgets(buffer1, 101, stdin);

    char *buffer2 = (char *)malloc(1024);
    if (buffer2 == NULL) {
        free(buffer1);
        return 1;
    }
    fgets(buffer2, 101, stdin);

    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        free(buffer1);
        free(buffer2);
        return 1;
    }

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buffer1);
        free(buffer2);
        free(buf);
        return 1;
    }

    fgets(buf, 1025, stdin);

    free(buffer1);
    free(buffer2);
    free(buf);
    free(buf1);

    return 0;
}