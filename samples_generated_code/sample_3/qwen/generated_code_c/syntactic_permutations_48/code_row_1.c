#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* img(const char* file) {
    FILE *fp;
    long lSize;
    char *buffer;

    fp = fopen(file, "rb");
    if (!fp) {
        perror("Error opening file");
        exit(1);
    }

    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);

    buffer = (char*)malloc(lSize + 1);
    if (!buffer) {
        fclose(fp);
        fputs("Memory allocation error", stderr);
        exit(1);
    }

    fread(buffer, 1, lSize, fp);
    fclose(fp);

    buffer[lSize] = '\0';

    return buffer;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(1);
    }

    const char* file = argv[1];
    char* result = img(file);

    printf("File content:\n%s\n", result);

    free(result);
    return 0;
}