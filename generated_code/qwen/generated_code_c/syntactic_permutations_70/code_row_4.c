#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILENAME_LENGTH 256

void create_uploads_directory() {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0700);
    }
}

int upload_file(const char *filename, const unsigned char *buffer, size_t buffer_size) {
    create_uploads_directory();

    char filepath[MAX_FILENAME_LENGTH];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);

    FILE *file = fopen(filepath, "wb");
    if (!file) {
        return -1;
    }

    size_t written = fwrite(buffer, 1, buffer_size, file);
    fclose(file);

    return (written == buffer_size) ? 0 : -1;
}

int main() {
    // Example usage of upload_file
    const char *filename = "example.txt";
    unsigned char content[] = "Hello, this is an example file content.";
    size_t content_size = sizeof(content) - 1; // Exclude the null terminator

    if (upload_file(filename, content, content_size) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }

    return 0;
}