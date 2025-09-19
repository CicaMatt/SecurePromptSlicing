#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define UPLOAD_DIR "uploads"
#define BUFFER_SIZE 1024

void create_directory(const char *dir) {
    if (mkdir(dir, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create directory");
        exit(EXIT_FAILURE);
    }
}

int upload_file(const char *filename, const unsigned char *data, size_t data_length) {
    FILE *file;
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);

    file = fopen(path, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return -1;
    }

    fwrite(data, 1, data_length, file);
    fclose(file);
    return 0;
}

int main(int argc, char *argv[]) {
    create_directory(UPLOAD_DIR);

    // Example usage:
    const char *test_filename = "example.txt";
    const unsigned char test_data[] = "This is a test file content.";
    size_t test_data_length = sizeof(test_data) - 1; // Exclude null terminator

    if (upload_file(test_filename, test_data, test_data_length) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }

    return 0;
}