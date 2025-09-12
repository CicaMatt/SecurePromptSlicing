#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0L, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char *buffer = malloc(filesize);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    size_t result = fread(buffer, 1, filesize, file);
    if (result != filesize) {
        perror("Reading error");
        free(buffer);
        fclose(file);
        return;
    }

    // Here you can process or output the buffer as needed
    fwrite(buffer, 1, filesize, stdout);

    free(buffer);
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