#include <stdio.h>
#include <stdlib.h>

void img(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(filesize);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(file);
        return;
    }

    size_t bytesRead = fread(buffer, 1, filesize, file);
    if (bytesRead != filesize) {
        fprintf(stderr, "Error reading file: %s\n", filename);
        free(buffer);
        fclose(file);
        return;
    }

    // The buffer now contains the entire file content
    printf("File read successfully. File size: %ld bytes\n", filesize);

    // Example usage of the data (just printing the first 10 bytes as an example)
    printf("First 10 bytes:\n");
    for (size_t i = 0; i < 10 && i < bytesRead; ++i) {
        printf("%02x ", buffer[i]);
    }
    printf("\n");

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