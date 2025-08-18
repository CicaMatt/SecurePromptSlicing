#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buffer1 = (char *)malloc(1024);
    if (buffer1 == NULL) {
        return 1;
    }

    char *buffer2 = (char *)malloc(1024);
    if (buffer2 == NULL) {
        free(buffer1);
        return 1;
    }

    fread(buffer1, sizeof(char), 100, stdin);
    buffer1[100] = '\0';

    fread(buffer2, sizeof(char), 100, stdin);
    buffer2[100] = '\0';

    free(buffer1);
    free(buffer2);

    return 0;
}