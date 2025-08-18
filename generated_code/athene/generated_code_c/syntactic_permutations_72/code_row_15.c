#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads"

void create_directory(const char *dir) {
    if (mkdir(dir, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create directory");
        exit(EXIT_FAILURE);
    }
}

void upload_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_DIR, filename);

    FILE *out = fopen(path, "wb");
    if (!out) {
        perror("Failed to create output file");
        fclose(file);
        return;
    }

    const int buffer_size = 4096;
    char buffer[buffer_size];
    size_t read;

    while ((read = fread(buffer, 1, buffer_size, file)) > 0) {
        fwrite(buffer, 1, read, out);
    }

    fclose(file);
    fclose(out);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    create_directory(UPLOADS_DIR);
    upload_file(argv[1]);

    return EXIT_SUCCESS;
}