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

    char input[1025];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        strncpy(buf, input, 100);
        buf[100] = '\0';
        strncpy(buf1, input, 100);
        buf1[100] = '\0';
    }

    free(buf);
    free(buf1);

    return 0;
}