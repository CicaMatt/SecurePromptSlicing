#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char* filename) {
    FILE *file;
    char *buffer;
    long length;

    file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return;
    }

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = malloc(length);
    if (buffer == NULL) {
        fprintf(stderr, "Memory error!\n");
        fclose(file);
        return;
    }

    fread(buffer, 1, length, file);
    fclose(file);

    fwrite(buffer, 1, length, stdout);

    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    img(argv[1]);

    return 0;
}