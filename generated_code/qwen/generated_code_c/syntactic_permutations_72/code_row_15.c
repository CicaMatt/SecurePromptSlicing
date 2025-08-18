#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOADS_DIR "uploads"

void create_uploads_directory() {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0700);
    }
}

void upload_file(const char* filename) {
    create_uploads_directory();

    FILE *source = fopen(filename, "rb");
    if (!source) {
        perror("Error opening file");
        return;
    }

    char destination_path[1024];
    snprintf(destination_path, sizeof(destination_path), "%s/%s", UPLOADS_DIR, filename);

    FILE *destination = fopen(destination_path, "wb");
    if (!destination) {
        perror("Error creating file in uploads directory");
        fclose(source);
        return;
    }

    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes_read, destination);
    }

    fclose(source);
    fclose(destination);
}

int main() {
    const char* filename = "example.txt";
    upload_file(filename);
    return 0;
}