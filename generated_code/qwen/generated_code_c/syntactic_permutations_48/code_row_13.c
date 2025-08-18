#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char *filename) {
    FILE *file;
    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        perror("Memory allocation error");
        fclose(file);
        return;
    }

    fread(buffer, 1, fileSize, file);
    fclose(file);

    fwrite(buffer, 1, fileSize, stdout);

    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    img(argv[1]);
    return EXIT_SUCCESS;
}