#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = malloc(1024);
    if (buf == NULL) return 1;
    char *buf1 = malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        return 1;
    }

    fgets(buf, 101, stdin);
    fgets(buf1, 101, stdin);

    free(buf);
    free(buf1);

    return 0;
}