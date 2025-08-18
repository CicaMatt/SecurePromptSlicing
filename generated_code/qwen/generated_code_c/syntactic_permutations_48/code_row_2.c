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
    long fileSize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        fclose(fp);
        return;
    }

    fread(buffer, fileSize, 1, fp);
    fclose(fp);

    fwrite(buffer, fileSize, 1, stdout);
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