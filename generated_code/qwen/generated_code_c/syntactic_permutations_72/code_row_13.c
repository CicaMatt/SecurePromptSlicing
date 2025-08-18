#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

void upload_file(const char *filename) {
    const char *upload_dir = "uploads";
    create_directory(upload_dir);

    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/%s", upload_dir, filename);

    FILE *src = fopen(filename, "rb");
    if (!src) {
        perror("Failed to open source file");
        return;
    }

    FILE *dst = fopen(full_path, "wb");
    if (!dst) {
        perror("Failed to create destination file");
        fclose(src);
        return;
    }

    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes_read, dst);
    }

    fclose(src);
    fclose(dst);
}

int main() {
    const char *filename = "example.txt";
    upload_file(filename);
    return 0;
}