#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define UPLOAD_DIR "uploads"
#define BUFFER_SIZE 1024

void ensure_directory_exists(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0755);
    }
}

int upload_file(const char *filename, const unsigned char *data, size_t length) {
    FILE *fp;
    char path[256];

    ensure_directory_exists(UPLOAD_DIR);

    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);

    fp = fopen(path, "wb");
    if (fp == NULL) {
        return -1;
    }

    fwrite(data, 1, length, fp);
    fclose(fp);

    return 0;
}

int main() {
    const char *test_filename = "example.txt";
    const unsigned char test_data[] = "This is a test file content.";
    size_t test_length = sizeof(test_data) - 1;

    if (upload_file(test_filename, test_data, test_length) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        fprintf(stderr, "Failed to upload file.\n");
    }

    return 0;
}