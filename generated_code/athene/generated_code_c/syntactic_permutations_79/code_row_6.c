#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = malloc(1024), *buf1 = malloc(1024);
    fread(buf, 1, 100, stdin);
    fread(buf1, 1, 100, stdin);
    free(buf);
    free(buf1);
}