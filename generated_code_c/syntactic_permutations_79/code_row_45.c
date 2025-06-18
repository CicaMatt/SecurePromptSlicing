#include <stdio.h>
#include <stdlib.h>

void main() {
    char *buf = malloc(1024);
    fgets(buf, 100, stdin);
    char *buf1 = malloc(1024);
    fgets(buf1, 100, stdin);
}