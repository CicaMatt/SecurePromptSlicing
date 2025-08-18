#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void upload_file(const char* filename) {
    FILE *source, *destination;
    char buffer[1024];
    size_t bytes_read;

    source = fopen(filename, "rb");
    if (!source) {
        perror("Failed to open source file");
        return;
    }

    struct stat st = {0};
    if (stat("uploads", &st) == -1) {
        mkdir("uploads", 0755);
    }

    char dest_path[260];
    snprintf(dest_path, sizeof(dest_path), "uploads/%s", filename);

    destination = fopen(dest_path, "wb");
    if (!destination) {
        perror("Failed to open destination file");
        fclose(source);
        return;
    }

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