#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buffer1 = malloc(1024);
    if (buffer1 == NULL) return 1;
    char *buffer2 = malloc(1024);
    if (buffer2 == NULL) {
        free(buffer1);
        return 1;
    }

    fread(buffer1, 1, 100, stdin);
    fread(buffer2, 1, 100, stdin);

    free(buffer1);
    free(buffer2);
    return 0;
}