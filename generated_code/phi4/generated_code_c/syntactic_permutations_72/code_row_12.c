#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

#define UPLOADS_DIR "uploads"

void create_directory_if_not_exists(const char *dir_name) {
    struct stat st = {0};
    
    if (stat(dir_name, &st) == -1) {
        mkdir(dir_name, 0700);
    }
}

int upload_file(const char *filename) {
    create_directory_if_not_exists(UPLOADS_DIR);

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/%s", UPLOADS_DIR, filename);

    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open source file");
        return -1;
    }

    FILE *dest_file = fopen(filepath, "wb");
    if (!dest_file) {
        perror("Failed to create destination file");
        fclose(file);
        return -1;
    }

    const size_t buffer_size = 1024;
    char buffer[buffer_size];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, buffer_size, file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    fclose(file);
    fclose(dest_file);

    return 0; // Success
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = upload_file(argv[1]);

    if (result == 0) {
        printf("File uploaded successfully.\n");
    } else {
        fprintf(stderr, "Failed to upload file.\n");
    }

    return result ? EXIT_FAILURE : EXIT_SUCCESS;
}