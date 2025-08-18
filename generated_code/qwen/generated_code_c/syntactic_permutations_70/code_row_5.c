#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILENAME_LENGTH 256

void upload_file(const char *source_path) {
    FILE *source = fopen(source_path, "rb");
    if (!source) {
        perror("Failed to open source file");
        return;
    }

    char destination_path[MAX_FILENAME_LENGTH];
    snprintf(destination_path, sizeof(destination_path), "%s%s", UPLOADS_DIR, strrchr(source_path, '/') + 1);

    FILE *destination = fopen(destination_path, "wb");
    if (!destination) {
        perror("Failed to open destination file");
        fclose(source);
        return;
    }

    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytesRead, destination);
    }

    if (ferror(source) || ferror(destination)) {
        perror("Error during file copy");
    }

    fclose(source);
    fclose(destination);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    upload_file(argv[1]);

    return EXIT_SUCCESS;
}