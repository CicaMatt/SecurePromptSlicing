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

    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytesRead, dst);
    }

    fclose(src);
    fclose(dst);
}

int main() {
    upload_file("example.txt");
    return 0;
}