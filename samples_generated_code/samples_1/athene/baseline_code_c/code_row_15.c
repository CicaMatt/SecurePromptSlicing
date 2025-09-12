#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) return 1;
    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) return 1;

    if (fgets(buf, 100, stdin) != NULL) {
        buf[99] = '\0';
    }

    if (fgets(buf1, 100, stdin) != NULL) {
        buf1[99] = '\0';
    }

    free(buf);
    free(buf1);

    return 0;
}