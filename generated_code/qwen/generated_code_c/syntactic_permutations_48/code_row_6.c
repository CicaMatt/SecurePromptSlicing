#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char* filename) {
    FILE *file;
    char *buffer;
    long fileLen;

    // Open file
    file = fopen(filename, "rb");
    if (!file) {
        perror("Unable to open file!");
        return;
    }

    // Get file length
    fseek(file, 0, SEEK_END);
    fileLen=ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory
    buffer=(char *)malloc(fileLen+1);
    if (!buffer) {
        fclose(file);
        fputs("Memory error!", stderr);
        return;
    }

    // Read file contents into buffer
    fread(buffer, fileLen, 1, file);
    fclose(file);

    // Output the file content
    fwrite(buffer, fileLen, 1, stdout);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    img(argv[1]);
    return 0;
}