#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *source = malloc(100);
    if (source == NULL) return 1;
    strcpy(source, "This is a test message to copy.");

    char *destination = malloc(100);
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