#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char* filename) {
    FILE *file;
    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fseek(file, 0L, SEEK_END);
    long sz = ftell(file);
    rewind(file);

    char *buffer = (char*)malloc(sz * sizeof(char));
    if (buffer == NULL) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    size_t result = fread(buffer, 1, sz, file);
    if (result != sz) {
        free(buffer);
        fclose(file);
        fprintf(stderr, "Reading error\n");
        return;
    }

    // Here you would typically send the buffer over a network or process it
    printf("File content read successfully. Size: %ld bytes\n", sz);

    free(buffer);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}