#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256

void img(const char *filename) {
    FILE *file;
    char buffer[1024];
    size_t bytesRead;

    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}