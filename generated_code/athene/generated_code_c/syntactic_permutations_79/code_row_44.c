#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = malloc(1024);
    if (buf == NULL) return 1;
    char *buf1 = malloc(1024);
    if (buf1 == NULL) return 1;

    fread(buf, 1, 100, stdin);
    fread(buf1, 1, 100, stdin);

    free(buf);
    free(buf1);
    return 0;
}