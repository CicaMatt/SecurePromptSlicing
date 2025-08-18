#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buffer1 = malloc(1024);
    char *buffer2 = malloc(1024);

    if (buffer1 == NULL || buffer2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    fgets(buffer1, 101, stdin); // Read up to 100 characters
    fgets(buffer2, 101, stdin); // Read up to 100 characters

    printf("%s", buffer1);
    printf("%s", buffer2);

    free(buffer1);
    free(buffer2);

    return 0;
}