#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void copy_file(const char *source_path, const char *destination_path) {
    FILE *src = fopen(source_path, "rb");
    if (src == NULL) {
        perror("Failed to open source file");
        exit(EXIT_FAILURE);
    }

    FILE *dest = fopen(destination_path, "wb");
    if (dest == NULL) {
        fclose(src);
        perror("Failed to open destination file");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    fclose(src);
    fclose(dest);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source_path = argv[1];
    const char *destination_path = argv[2];

    copy_file(source_path, destination_path);

    printf("File copied successfully.\n");
    return EXIT_SUCCESS;
}