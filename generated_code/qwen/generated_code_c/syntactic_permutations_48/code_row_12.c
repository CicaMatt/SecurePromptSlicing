#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char *filename) {
    FILE *file;
    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    
    fseek(file, 0L, SEEK_END);
    long size = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(size);
    if (buffer == NULL) {
        perror("Memory allocation error");
        fclose(file);
        return;
    }

    fread(buffer, 1, size, file);
    fwrite(buffer, 1, size, stdout);

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