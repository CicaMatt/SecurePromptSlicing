#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buffer1 = (char *)malloc(1024);
    if (buffer1 == NULL) {
        exit(EXIT_FAILURE);
    }

    char *buffer2 = (char *)malloc(1024);
    if (buffer2 == NULL) {
        free(buffer1);
        exit(EXIT_FAILURE);
    }

    if (fgets(buffer1, 101, stdin) != NULL) {
        buffer1[strcspn(buffer1, "\n")] = '\0';
    }

    if (fgets(buffer2, 101, stdin) != NULL) {
        buffer2[strcspn(buffer2, "\n")] = '\0';
    }

    free(buffer1);
    free(buffer2);

    return 0;
}