#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    char *buffer = malloc(size);

    if (buffer == NULL) {
        perror("Failed to allocate buffer");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        printf("%c", buffer[i]);
    }
    printf("\n");

    free(buffer);
    return 0;
}