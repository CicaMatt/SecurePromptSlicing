#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

void copy_file(const char *src_path, const char *dest_dir) {
    FILE *src = fopen(src_path, "rb");
    if (!src) {
        perror("Failed to open source file");
        exit(EXIT_FAILURE);
    }

    char dest_path[256];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", dest_dir, strrchr(src_path, '/') ? strrchr(src_path, '/') + 1 : src_path);

    FILE *dest = fopen(dest_path, "wb");
    if (!dest) {
        perror("Failed to open destination file");
        fclose(src);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
        fwrite(buffer, 1, bytes_read, dest);
    }

    fclose(src);
    fclose(dest);

    printf("File copied to %s\n", dest_path);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_pdf> <upload_directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *src_path = argv[1];
    const char *dest_dir = argv[2];

    // Create uploads directory if it doesn't exist
    struct stat st = {0};
    if (stat(dest_dir, &st) == -1) {
        mkdir(dest_dir, 0700);
    }

    copy_file(src_path, dest_dir);

    return EXIT_SUCCESS;
}