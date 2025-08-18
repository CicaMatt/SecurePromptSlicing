#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0755);
    }
}

void upload_file(const char *filename) {
    const char *directory = "uploads";
    create_directory(directory);

    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/%s", directory, filename);

    FILE *source_file = fopen(filename, "rb");
    if (!source_file) {
        perror("Failed to open source file");
        return;
    }

    FILE *destination_file = fopen(full_path, "wb");
    if (!destination_file) {
        perror("Failed to create destination file");
        fclose(source_file);
        return;
    }

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        fwrite(buffer, 1, bytes_read, destination_file);
    }

    fclose(source_file);
    fclose(destination_file);
}

int main() {
    upload_file("example.txt");
    return 0;
}