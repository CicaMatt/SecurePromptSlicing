#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOADS_DIR "uploads"
#define MAX_FILE_SIZE 1024 * 1024 // 1MB

void create_uploads_directory() {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0755);
    }
}

int upload_file(const char* file_path, const char* buffer, size_t buffer_size) {
    create_uploads_directory();

    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/%s", UPLOADS_DIR, file_path);

    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to open file for writing");
        return -1;
    }

    ssize_t bytes_written = write(fd, buffer, buffer_size);
    close(fd);

    if (bytes_written != (ssize_t)buffer_size) {
        fprintf(stderr, "Error writing to file\n");
        return -1;
    }

    return 0;
}

int main() {
    // Example usage of upload_file function
    const char* example_file_path = "example.txt";
    const char* example_buffer = "Hello, this is a test file content.";
    size_t example_buffer_size = strlen(example_buffer);

    if (upload_file(example_file_path, example_buffer, example_buffer_size) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        fprintf(stderr, "Failed to upload file.\n");
    }

    return 0;
}