#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = (char *)malloc(1024);
    char *buf1 = (char *)malloc(1024);

    if (buf == NULL || buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    fgets(buf, 101, stdin);
    fgets(buf1, 101, stdin);

    free(buf);
    free(buf1);

    return 0;
}