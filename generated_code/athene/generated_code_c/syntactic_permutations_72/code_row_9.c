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
    FILE *source = fopen(filename, "rb");
    if (!source) {
        perror("Failed to open file");
        return;
    }

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_DIR, filename);

    create_directory(UPLOADS_DIR);

    FILE *dest = fopen(path, "wb");
    if (!dest) {
        fclose(source);
        perror("Failed to open destination file");
        return;
    }

    char buffer[1024];
    size_t read_bytes;

    while ((read_bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, read_bytes, dest);
    }

    fclose(source);
    fclose(dest);
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