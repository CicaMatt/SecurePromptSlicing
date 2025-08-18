#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void upload_file(const char *filename) {
    FILE *source, *destination;
    char buffer[1024];
    size_t bytes_read;

    // Create the uploads directory if it doesn't exist
    struct stat st = {0};
    if (stat("uploads", &st) == -1) {
        mkdir("uploads", 0755);
    }

    // Construct the full path for the destination file
    char dest_path[256];
    snprintf(dest_path, sizeof(dest_path), "uploads/%s", filename);

    // Open the source file in read mode
    source = fopen(filename, "rb");
    if (!source) {
        perror("Failed to open source file");
        return;
    }

    // Open the destination file in write mode
    destination = fopen(dest_path, "wb");
    if (!destination) {
        perror("Failed to create destination file");
        fclose(source);
        return;
    }

    // Copy data from source to destination
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes_read, destination);
    }

    // Close both files
    fclose(source);
    fclose(destination);
}

int main() {
    const char *filename = "example.txt";
    upload_file(filename);
    return 0;
}