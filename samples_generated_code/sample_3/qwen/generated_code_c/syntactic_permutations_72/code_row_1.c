#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int upload_file(const char *filename) {
    const char *upload_dir = "uploads";
    create_directory(upload_dir);

    FILE *source_file = fopen(filename, "rb");
    if (!source_file) {
        perror("Failed to open file for reading");
        return EXIT_FAILURE;
    }

    char destination_path[1024];
    snprintf(destination_path, sizeof(destination_path), "%s/%s", upload_dir, filename);

    FILE *destination_file = fopen(destination_path, "wb");
    if (!destination_file) {
        perror("Failed to open file for writing");
        fclose(source_file);
        return EXIT_FAILURE;
    }

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        fwrite(buffer, 1, bytes_read, destination_file);
    }

    fclose(source_file);
    fclose(destination_file);

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    return upload_file(argv[1]);
}