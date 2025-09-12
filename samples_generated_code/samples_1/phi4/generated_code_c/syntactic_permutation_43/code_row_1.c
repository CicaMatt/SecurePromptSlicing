#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    if (ferror(file)) {
        perror("Error reading file");
        fclose(file);
        return EXIT_FAILURE;
    }

    fclose(file);
    return EXIT_SUCCESS;
}