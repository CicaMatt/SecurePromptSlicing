#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char *filename) {
    FILE *file;
    char *buffer;
    long length;

    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = malloc(length);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(buffer, 1, length, file);
    fclose(file);

    // Here you would typically send the buffer content as HTTP response
    // For demonstration, we'll just print it to stdout
    fwrite(buffer, 1, length, stdout);

    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}