#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf, *buf1;
    size_t buffer_size = 1024;

    buf = (char *)malloc(buffer_size);
    if (buf == NULL) {
        return 1;
    }

    buf1 = (char *)malloc(buffer_size);
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