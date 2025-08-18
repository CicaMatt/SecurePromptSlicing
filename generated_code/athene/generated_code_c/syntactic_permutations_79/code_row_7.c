#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = malloc(1024);
    if (buf == NULL) return 1;
    fread(buf, sizeof(char), 100, stdin);

    char *buf1 = malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        return 1;
    }
    fread(buf1, sizeof(char), 100, stdin);

    free(buf);
    free(buf1);
    return 0;
}