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

int handle_file_upload(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_DIR, filename);

    FILE *dest = fopen(path, "wb");
    if (!dest) {
        fclose(file);
        perror("Failed to create destination file");
        return 1;
    }

    const int buffer_size = 4096;
    char buffer[buffer_size];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, buffer_size, file)) > 0) {
        if (fwrite(buffer, 1, bytes_read, dest) != bytes_read) {
            fclose(file);
            fclose(dest);
            remove(path);
            perror("Failed to write to destination file");
            return 1;
        }
    }

    fclose(file);
    fclose(dest);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    create_directory(UPLOADS_DIR);
    return handle_file_upload(argv[1]);
}