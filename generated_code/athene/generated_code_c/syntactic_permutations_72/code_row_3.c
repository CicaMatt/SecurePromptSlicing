#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOAD_DIR "uploads"

void create_directory(const char *dir) {
    if (mkdir(dir, 0755) != 0 && errno != EEXIST) {
        perror("Failed to create directory");
        exit(EXIT_FAILURE);
    }
}

void upload_file(const char *filename) {
    FILE *source = fopen(filename, "rb");
    if (!source) {
        perror("Failed to open file");
        return;
    }

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);

    create_directory(UPLOAD_DIR);

    FILE *destination = fopen(path, "wb");
    if (!destination) {
        perror("Failed to open destination file");
        fclose(source);
        return;
    }

    const int bufferSize = 1024;
    char buffer[bufferSize];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, bufferSize, source)) > 0) {
        fwrite(buffer, 1, bytesRead, destination);
    }

    fclose(source);
    fclose(destination);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    upload_file(argv[1]);
    printf("File uploaded successfully.\n");

    return EXIT_SUCCESS;
}