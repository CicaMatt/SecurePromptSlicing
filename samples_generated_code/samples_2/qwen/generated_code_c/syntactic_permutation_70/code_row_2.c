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

int upload_file(const char* file_name, const char* content, size_t content_length) {
    create_uploads_directory();

    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%s", UPLOADS_DIR, file_name);

    FILE *fp = fopen(full_path, "wb");
    if (fp == NULL) {
        return 1;
    }

    size_t written = fwrite(content, 1, content_length, fp);
    fclose(fp);

    if (written != content_length) {
        remove(full_path);
        return 1;
    }

    return 0;
}

int main() {
    const char* file_name = "example.txt";
    const char* file_content = "This is a test file content.";
    size_t file_size = strlen(file_content);

    if (file_size > MAX_FILE_SIZE) {
        printf("File too large.\n");
        return 1;
    }

    int result = upload_file(file_name, file_content, file_size);
    if (result == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }

    return result;
}