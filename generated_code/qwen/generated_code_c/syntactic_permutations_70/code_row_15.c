#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILE_SIZE 1024 * 1024 // 1MB

void create_uploads_directory() {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0755);
    }
}

int upload_file(const char *filename, const char *content, size_t content_length) {
    create_uploads_directory();

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);

    FILE *file = fopen(filepath, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return -1;
    }

    size_t bytes_written = fwrite(content, 1, content_length, file);
    fclose(file);

    if (bytes_written != content_length) {
        fprintf(stderr, "Error writing to file\n");
        return -1;
    }

    return 0;
}

int main() {
    const char *filename = "example.txt";
    const char *content = "This is a test file content.";
    size_t content_length = strlen(content);

    if (upload_file(filename, content, content_length) == 0) {
        printf("File uploaded successfully\n");
    } else {
        printf("Failed to upload file\n");
    }

    return 0;
}