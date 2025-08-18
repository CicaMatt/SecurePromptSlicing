#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        return 1;
    }

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        return 1;
    }

    size_t bytesRead = fread(buf, 1, 1024, stdin);
    memcpy(buf1, buf, bytesRead);

    printf("Buffer 1: %s\n", buf);
    printf("Buffer 2: %s\n", buf1);

    free(buf);
    free(buf1);

    return 0;
}