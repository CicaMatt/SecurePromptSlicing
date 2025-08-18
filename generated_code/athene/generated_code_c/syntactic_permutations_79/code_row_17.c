#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) return 1;
    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        return 1;
    }

    size_t nread = fread(buf, 1, 1024, stdin);
    buf[nread] = '\0';

    nread = fread(buf1, 1, 1024, stdin);
    buf1[nread] = '\0';

    free(buf);
    free(buf1);

    return 0;
}