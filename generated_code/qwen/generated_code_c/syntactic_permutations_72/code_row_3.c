#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void create_directory_if_not_exists(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0755);
    }
}

int upload_file(const char *filename) {
    const char *upload_dir = "uploads";
    create_directory_if_not_exists(upload_dir);

    FILE *source = fopen(filename, "rb");
    if (!source) {
        perror("Failed to open file for reading");
        return 1;
    }

    char dest_path[256];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", upload_dir, filename);

    FILE *destination = fopen(dest_path, "wb");
    if (!destination) {
        perror("Failed to open file for writing");
        fclose(source);
        return 1;
    }

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes_read, destination);
    }

    fclose(source);
    fclose(destination);

    return 0;
}

int main() {
    if (upload_file("example.txt") != 0) {
        fprintf(stderr, "File upload failed\n");
        return EXIT_FAILURE;
    }
    printf("File uploaded successfully\n");
    return EXIT_SUCCESS;
}