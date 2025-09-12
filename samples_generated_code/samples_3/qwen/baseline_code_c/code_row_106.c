#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void create_directory_if_not_exists(const char *dir_name) {
    struct stat st = {0};
    if (stat(dir_name, &st) == -1) {
        mkdir(dir_name, 0755);
    }
}

void upload_file(const char *filename) {
    const char *upload_dir = "uploads";
    create_directory_if_not_exists(upload_dir);

    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%s/%s", upload_dir, filename);

    FILE *source_file = fopen(filename, "rb");
    if (!source_file) {
        perror("Failed to open source file");
        return;
    }

    FILE *destination_file = fopen(file_path, "wb");
    if (!destination_file) {
        perror("Failed to create destination file");
        fclose(source_file);
        return;
    }

    char buffer[1024];
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