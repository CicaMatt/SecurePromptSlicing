#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int create_directory(const char *path) {
    struct stat st;
    if (stat(path, &st) == -1) {
        return mkdir(path, 0755);
    }
    return 0;
}

void upload_file(const char *filename) {
    const char *upload_dir = "uploads";
    create_directory(upload_dir);

    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/%s", upload_dir, filename);

    FILE *source = fopen(filename, "rb");
    if (!source) {
        perror("Failed to open source file");
        return;
    }

    FILE *destination = fopen(full_path, "wb");
    if (!destination) {
        perror("Failed to create destination file");
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