#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads"

void create_uploads_dir() {
    if (mkdir(UPLOADS_DIR, 0755) != 0 && errno != EEXIST) {
        perror("Failed to create uploads directory");
        exit(EXIT_FAILURE);
    }
}

void upload_(const char *name) {
    FILE *source = fopen(name, "rb");
    if (!source) {
        perror("Failed to open source file");
        return;
    }

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_DIR, name);

    FILE *destination = fopen(path, "wb");
    if (!destination) {
        perror("Failed to create destination file");
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

    create_uploads_dir();
    upload_(argv[1]);

    return EXIT_SUCCESS;
}