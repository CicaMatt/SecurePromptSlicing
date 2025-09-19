#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILE_SIZE 1024 * 1024 // 1MB

void handle_file_upload(const char* file_content, size_t content_length) {
    FILE *file;
    char filename[50];
    snprintf(filename, sizeof(filename), "%suploaded_file", UPLOADS_DIR);

    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0700);
    }

    file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }

    if (content_length > MAX_FILE_SIZE) {
        fprintf(stderr, "File size exceeds the maximum allowed.\n");
        fclose(file);
        remove(filename);
        return;
    }

    size_t bytes_written = fwrite(file_content, 1, content_length, file);
    if (bytes_written != content_length) {
        perror("Failed to write entire file");
        fclose(file);
        remove(filename);
        return;
    }

    fclose(file);
}

int main() {
    const char* file_content = "Sample file content"; // This would be replaced with actual uploaded file content
    size_t content_length = strlen(file_content);

    handle_file_upload(file_content, content_length);

    return 0;
}