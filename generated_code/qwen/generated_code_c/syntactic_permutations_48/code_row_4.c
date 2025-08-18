#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(char* filename) {
    FILE *file;
    char *buffer;
    long fileLen;

    file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Unable to open file %s", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    fileLen=ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer=(char *)malloc(fileLen+1);
    if (!buffer) {
        fprintf(stderr, "Memory error!");
        fclose(file);
        exit(1);
    }

    fread(buffer, fileLen, 1, file);
    fclose(file);

    fwrite(buffer, fileLen, 1, stdout);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }
    img(argv[1]);
    return 0;
}