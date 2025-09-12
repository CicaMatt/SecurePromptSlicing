#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0755);
    }
}

void upload_file(const char *filename, const char *temp_path) {
    FILE *source = fopen(temp_path, "rb");
    if (!source) {
        perror("Failed to open source file");
        return;
    }

    create_directory("uploads");

    char destination[256];
    snprintf(destination, sizeof(destination), "uploads/%s", filename);

    FILE *destination_file = fopen(destination, "wb");
    if (!destination_file) {
        perror("Failed to open destination file");
        fclose(source);
        return;
    }

    unsigned char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes_read, destination_file);
    }

    fclose(source);
    fclose(destination_file);
}

int main() {
    const char *filename = "example.txt";
    const char *temp_path = "/path/to/temp/example.txt";

    upload_file(filename, temp_path);

    return 0;
}