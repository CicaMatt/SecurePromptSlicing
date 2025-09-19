#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(10 * sizeof(char));
    if (buf == NULL) return 1;
    fread(buf, sizeof(char), 10, stdin);
    free(buf);
    return 0;
}