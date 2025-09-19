#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILE_SIZE 1048576 // 1MB

void create_uploads_directory() {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0700);
    }
}

int upload_file(const char *filename, const char *file_content, size_t file_size) {
    if (file_size > MAX_FILE_SIZE) {
        return -1; // File too large
    }

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);

    FILE *fp = fopen(filepath, "wb");
    if (!fp) {
        return -2; // Failed to open file for writing
    }

    size_t written = fwrite(file_content, 1, file_size, fp);
    fclose(fp);

    if (written != file_size) {
        return -3; // Incomplete write
    }

    return 0; // Success
}

int main() {
    create_uploads_directory();

    const char *filename = "example.txt";
    const char *file_content = "Hello, this is a test file.";
    size_t file_size = strlen(file_content);

    int result = upload_file(filename, file_content, file_size);
    if (result == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file. Error code: %d\n", result);
    }

    return 0;
}