#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char* file) {
    FILE *fp;
    fp = fopen(file, "rb");
    if (fp == NULL) {
        perror("Failed to open file");
        return;
    }
    fseek(fp, 0L, SEEK_END);
    long sz = ftell(fp);
    rewind(fp);

    char *buffer = malloc(sz + 1);
    if (!buffer) {
        fclose(fp);
        perror("Memory allocation failed");
        return;
    }

    fread(buffer, 1, sz, fp);
    fclose(fp);

    fwrite(buffer, 1, sz, stdout);

    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    img(argv[1]);
    return 0;
}