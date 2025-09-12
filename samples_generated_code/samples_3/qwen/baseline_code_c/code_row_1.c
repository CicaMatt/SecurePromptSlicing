#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char *file) {
    FILE *fp;
    char *buffer = NULL;
    long length;

    fp = fopen(file, "rb");
    if (fp == NULL) {
        perror("Failed to open file");
        return;
    }

    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    buffer = malloc(length + 1);
    if (buffer) {
        fread(buffer, 1, length, fp);
        fwrite(buffer, 1, length, stdout);
        free(buffer);
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    img(argv[1]);
    return EXIT_SUCCESS;
}