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

    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/%s", upload_dir, filename);

    FILE *src = fopen(filename, "rb");
    if (!src) {
        perror("Failed to open source file");
        return;
    }

    FILE *dst = fopen(full_path, "wb");
    if (!dst) {
        fclose(src);
        perror("Failed to create destination file");
        return;
    }

    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes_read, dst);
    }

    fclose(src);
    fclose(dst);

    printf("File uploaded successfully to %s\n", full_path);
}

int main() {
    upload_file("example.txt");
    return 0;
}