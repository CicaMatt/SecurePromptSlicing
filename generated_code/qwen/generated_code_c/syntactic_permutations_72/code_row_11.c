#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void create_directory_if_not_exists(const char *dir_name) {
    struct stat st = {0};
    if (stat(dir_name, &st) == -1) {
        mkdir(dir_name, 0700);
    }
}

void upload_file(const char *filename) {
    const char *directory = "uploads";
    create_directory_if_not_exists(directory);

    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/%s", directory, filename);

    FILE *src_file = fopen(filename, "rb");
    if (!src_file) {
        perror("Failed to open source file");
        return;
    }

    FILE *dest_file = fopen(full_path, "wb");
    if (!dest_file) {
        fclose(src_file);
        perror("Failed to create destination file");
        return;
    }

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    fclose(src_file);
    fclose(dest_file);
}

int main() {
    const char *filename = "example.txt"; // Replace with the actual filename
    upload_file(filename);
    return 0;
}