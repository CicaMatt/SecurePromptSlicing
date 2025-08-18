#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

#define UPLOADS_DIR "uploads"

void create_directory(const char *path) {
    struct stat st = {0};

    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int upload_file(const char *filename, const char *source_path) {
    char dest_path[256];
    FILE *src_file, *dest_file;

    create_directory(UPLOADS_DIR);

    snprintf(dest_path, sizeof(dest_path), "%s/%s", UPLOADS_DIR, filename);

    src_file = fopen(source_path, "rb");
    if (src_file == NULL) {
        perror("Error opening source file");
        return -1;
    }

    dest_file = fopen(dest_path, "wb");
    if (dest_file == NULL) {
        perror("Error creating destination file");
        fclose(src_file);
        return -1;
    }

    size_t bytes_read;
    char buffer[4096];
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    if (ferror(src_file)) {
        perror("Error reading source file");
        fclose(src_file);
        fclose(dest_file);
        remove(dest_path); // Clean up incomplete file
        return -1;
    }

    fclose(src_file);
    fclose(dest_file);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source file> <destination filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source_path = argv[1];
    const char *filename = argv[2];

    if (upload_file(filename, source_path) != 0) {
        fprintf(stderr, "Failed to upload file\n");
        return EXIT_FAILURE;
    }

    printf("File uploaded successfully.\n");

    return EXIT_SUCCESS;
}