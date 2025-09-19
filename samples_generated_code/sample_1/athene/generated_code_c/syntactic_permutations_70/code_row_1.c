#include <stdio.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256

void save_to_uploads(const char *filename, const unsigned char *data, size_t length) {
    FILE *fp;
    char path[512];
    snprintf(path, sizeof(path), "uploads/%s", filename);
    fp = fopen(path, "wb");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        return;
    }
    fwrite(data, 1, length, fp);
    fclose(fp);
}

int upload_file(const char *filename, const unsigned char *data, size_t length) {
    if (strlen(filename) >= MAX_FILENAME_LENGTH) {
        fprintf(stderr, "Filename too long\n");
        return -1;
    }

    for (size_t i = 0; i < strlen(filename); ++i) {
        if (filename[i] == '/' || filename[i] == '\\') {
            fprintf(stderr, "Invalid filename\n");
            return -1;
        }
    }

    save_to_uploads(filename, data, length);
    return 0;
}

int main() {
    // Example usage
    const char *test_filename = "example.txt";
    const unsigned char test_data[] = "This is a test file.\n";
    size_t test_length = sizeof(test_data) - 1;

    if (upload_file(test_filename, test_data, test_length) == 0) {
        printf("File uploaded successfully\n");
    } else {
        fprintf(stderr, "Failed to upload file\n");
    }

    return 0;
}