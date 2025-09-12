#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(filesize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    size_t read_size = fread(buffer, 1, filesize, file);
    if (read_size != filesize) {
        fprintf(stderr, "Error reading file %s\n", filename);
        free(buffer);
        fclose(file);
        exit(EXIT_FAILURE);
    }
    
    buffer[filesize] = '\0';
    printf("File read successfully. Content:\n%s\n", buffer);

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