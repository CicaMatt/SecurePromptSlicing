#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        exit(1);
    }
    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        exit(1);
    }

    fgets(buf, 100, stdin);
    fgets(buf1, 100, stdin);

    free(buf);
    free(buf1);
    return 0;
}