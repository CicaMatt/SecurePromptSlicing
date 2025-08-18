#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buffer1 = malloc(1024);
    if (buffer1 == NULL) return 1;
    fgets(buffer1, 100, stdin);

    char *buffer2 = malloc(1024);
    if (buffer2 == NULL) return 1;
    fgets(buffer2, 100, stdin);

    free(buffer1);
    free(buffer2);
    return 0;
}