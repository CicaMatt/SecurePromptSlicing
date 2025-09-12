#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 256

void img(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("File not found\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size + 1);
    if (!buffer) {
        fclose(file);
        printf("Memory allocation failed\n");
        return;
    }

    fread(buffer, file_size, 1, file);
    buffer[file_size] = '\0';

    printf("%s", buffer);

    free(buffer);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}