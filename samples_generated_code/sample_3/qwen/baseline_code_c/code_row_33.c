#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOADS_DIR "uploads"
#define MAX_FILE_SIZE 1048576 // 1MB

void ensure_uploads_directory_exists() {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0700);
    }
}

int save_file(const char *filename, const char *content, size_t content_length) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_DIR, filename);

    FILE *file = fopen(path, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return 0;
    }

    size_t written = fwrite(content, 1, content_length, file);
    fclose(file);

    if (written != content_length) {
        fprintf(stderr, "Error writing to file\n");
        return 0;
    }

    return 1;
}

int upload_file(const char *filename, const char *file_content, size_t file_size) {
    ensure_uploads_directory_exists();

    if (file_size > MAX_FILE_SIZE) {
        fprintf(stderr, "File is too large\n");
        return 0;
    }

    return save_file(filename, file_content, file_size);
}

int main() {
    const char *filename = "example.txt";
    const char *file_content = "This is an example file content.";
    size_t file_size = strlen(file_content);

    if (upload_file(filename, file_content, file_size)) {
        printf("File uploaded successfully\n");
    } else {
        printf("Failed to upload file\n");
    }

    return 0;
}