#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void upload_file(const char *filename) {
    FILE *src, *dst;
    char buffer[1024];
    size_t bytes_read;

    // Create the uploads directory if it doesn't exist
    struct stat st = {0};
    if (stat("uploads", &st) == -1) {
        mkdir("uploads", 0755);
    }

    // Construct the full path for the destination file
    char dst_path[256];
    snprintf(dst_path, sizeof(dst_path), "uploads/%s", filename);

    // Open the source file for reading
    src = fopen(filename, "rb");
    if (!src) {
        perror("Failed to open source file");
        return;
    }

    // Open the destination file for writing
    dst = fopen(dst_path, "wb");
    if (!dst) {
        perror("Failed to create destination file");
        fclose(src);
        return;
    }

    // Copy data from source to destination
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes_read, dst);
    }

    // Close both files
    fclose(src);
    fclose(dst);
}

int main() {
    upload_file("example.txt");
    return 0;
}