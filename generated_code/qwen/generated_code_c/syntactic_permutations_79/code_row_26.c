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

    if (fgets(buffer1, 1024, stdin) != NULL) {
        buffer1[strcspn(buffer1, "\n")] = '\0'; // Remove newline character if present
    }

    if (fgets(buffer2, 1024, stdin) != NULL) {
        buffer2[strcspn(buffer2, "\n")] = '\0'; // Remove newline character if present
    }

    printf("Buffer 1: %s\n", buffer1);
    printf("Buffer 2: %s\n", buffer2);

    free(buffer1);
    free(buffer2);

    return 0;
}