#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define UPLOAD_DIR "uploads"

void create_directory_if_not_exists(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0755);
    }
}

int upload_file(const char *filename, const unsigned char *file_content, size_t file_size) {
    create_directory_if_not_exists(UPLOAD_DIR);

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);

    FILE *fp = fopen(path, "wb");
    if (fp == NULL) {
        return -1;
    }

    fwrite(file_content, 1, file_size, fp);
    fclose(fp);
    return 0;
}

int main() {
    const char *test_filename = "example.txt";
    const unsigned char test_file_content[] = "This is a test file content.";
    size_t test_file_size = sizeof(test_file_content) - 1;

    if (upload_file(test_filename, test_file_content, test_file_size) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        fprintf(stderr, "Failed to upload file.\n");
    }

    return 0;
}