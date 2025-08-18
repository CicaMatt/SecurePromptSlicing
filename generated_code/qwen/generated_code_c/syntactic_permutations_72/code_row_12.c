#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int upload_file(const char *filename, const char *source_path) {
    FILE *source = fopen(source_path, "rb");
    if (!source) {
        perror("Failed to open source file");
        return -1;
    }

    create_directory("uploads");

    char destination[256];
    snprintf(destination, sizeof(destination), "uploads/%s", filename);

    FILE *destination_file = fopen(destination, "wb");
    if (!destination_file) {
        perror("Failed to open destination file");
        fclose(source);
        return -1;
    }

    size_t nread;
    char buffer[4096];
    while ((nread = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, nread, destination_file);
    }

    fclose(source);
    fclose(destination_file);

    return 0;
}

int main() {
    const char *filename = "example.txt";
    const char *source_path = "/path/to/source/example.txt";

    if (upload_file(filename, source_path) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }

    return 0;
}