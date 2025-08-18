#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char* filename) {
    FILE *file;
    char *buffer = NULL;
    long length;

    file = fopen(filename, "rb");
    if (file) {
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer) {
            fread(buffer, 1, length, file);
            fwrite(buffer, 1, length, stdout); // Output to stdout
        }
        free(buffer);
        fclose(file);
    } else {
        perror("Error opening file");
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        img(argv[1]);
    } else {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    }
    return 0;
}