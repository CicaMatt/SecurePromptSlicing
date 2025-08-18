#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        return 1;
    }
    fgets(buf, 101, stdin);

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        return 1;
    }
    fgets(buf1, 1025, stdin);

    free(buf);
    free(buf1);
    return 0;
}