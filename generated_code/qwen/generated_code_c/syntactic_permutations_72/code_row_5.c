#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0777);
    }
}

void upload_file(const char *filename) {
    const char *upload_dir = "uploads";
    char file_path[256];

    create_directory(upload_dir);

    snprintf(file_path, sizeof(file_path), "%s/%s", upload_dir, filename);

    FILE *source = fopen(filename, "rb");
    if (!source) {
        perror("Failed to open source file");
        return;
    }

    FILE *destination = fopen(file_path, "wb");
    if (!destination) {
        perror("Failed to open destination file");
        fclose(source);
        return;
    }

    char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes_read, destination);
    }

    fclose(source);
    fclose(destination);
}

int main() {
    upload_file("example.txt");
    return 0;
}