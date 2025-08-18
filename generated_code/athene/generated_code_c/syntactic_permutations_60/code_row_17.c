#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    size_t buffer_size = atoi(argv[1]);
    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        perror("malloc");
        return 1;
    }

    printf(".\n");

    free(buffer);
    return 0;
}