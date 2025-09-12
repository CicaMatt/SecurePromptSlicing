#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FILE_SIZE 1024 * 1024 // 1MB
#define UPLOADS_DIR "uploads"

void create_uploads_directory() {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0755);
    }
}

int upload_file(const char *file_content, size_t file_size, const char *file_name) {
    if (file_size > MAX_FILE_SIZE) {
        return -1;
    }

    create_uploads_directory();

    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%s/%s", UPLOADS_DIR, file_name);

    FILE *fp = fopen(file_path, "wb");
    if (!fp) {
        return -1;
    }

    size_t written = fwrite(file_content, 1, file_size, fp);
    fclose(fp);

    if (written != file_size) {
        remove(file_path);
        return -1;
    }

    return 0;
}

int main() {
    const char *file_name = "example.txt";
    const char *file_content = "Hello, this is a test file content.";
    size_t file_size = strlen(file_content);

    if (upload_file(file_content, file_size, file_name) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }

    return 0;
}