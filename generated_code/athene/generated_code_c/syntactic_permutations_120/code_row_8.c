#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *source = malloc(20);
    if (source == NULL) return 1;
    strcpy(source, "Hello, World!");

    char *destination = malloc(20);
    if (destination == NULL) {
        free(source);
        return 1;
    }

    memcpy(destination, source, strlen(source) + 1);

    printf("%s\n", destination);

    free(source);
    free(destination);

    return 0;
}