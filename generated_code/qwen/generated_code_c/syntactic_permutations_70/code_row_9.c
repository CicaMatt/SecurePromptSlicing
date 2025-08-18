#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define UPLOAD_DIR "uploads/"
#define MAX_FILENAME_LENGTH 100

void ensure_directory_exists(const char *path) {
    struct stat st;
    if (stat(path, &st) == -1) {
        mkdir(path, 0755);
    }
}

int save_file_to_disk(const char *filename, const char *buffer, size_t length) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }
    fwrite(buffer, 1, length, file);
    fclose(file);
    return 1;
}

int upload_file(const char *filename, const char *buffer, size_t length) {
    ensure_directory_exists(UPLOAD_DIR);

    char full_path[MAX_FILENAME_LENGTH];
    snprintf(full_path, sizeof(full_path), "%s%s", UPLOAD_DIR, filename);

    if (save_file_to_disk(full_path, buffer, length)) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    const char *test_filename = "example.txt";
    const char *file_content = "This is a test file content.";
    size_t file_length = strlen(file_content);

    if (upload_file(test_filename, file_content, file_length)) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }

    return 0;
}