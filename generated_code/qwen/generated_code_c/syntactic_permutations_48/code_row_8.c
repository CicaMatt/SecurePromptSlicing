#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char* filename) {
    FILE *file;
    long length;
    unsigned char *data;

    file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Could not open file %s\n", filename);
        return;
    }

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);

    data = malloc(length);
    if (data == NULL) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    fread(data, 1, length, file);
    fclose(file);

    fwrite(data, 1, length, stdout);
    free(data);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);
    return EXIT_SUCCESS;
}