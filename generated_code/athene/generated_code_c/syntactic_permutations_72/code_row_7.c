#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads"

void create_directory(const char *dir) {
    if (mkdir(dir, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create directory");
        exit(1);
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

    FILE *dest = fopen(path, "wb");
    if (!dest) {
        perror("Failed to create destination file");
        fclose(file);
        return;
    }

    const int buffer_size = 1024;
    unsigned char buffer[buffer_size];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, buffer_size, file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest);
    }

    fclose(file);
    fclose(dest);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    create_directory(UPLOADS_DIR);
    upload_file(argv[1]);

    printf("File uploaded successfully.\n");
    return 0;
}