#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char *file) {
    FILE *fp = fopen(file, "rb");
    if (fp == NULL) {
        perror("Failed to open file");
        return;
    }

    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    unsigned char *buffer = malloc(size);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(fp);
        return;
    }

    fread(buffer, 1, size, fp);
    fwrite(buffer, 1, size, stdout);

    free(buffer);
    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}