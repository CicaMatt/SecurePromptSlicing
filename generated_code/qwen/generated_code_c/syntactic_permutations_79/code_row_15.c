#include <stdio.h>
#include <stdlib.h>

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

    size_t bytesRead = fread(buf, sizeof(char), 1024, stdin);

    free(buf);
    free(buf1);

    return 0;
}