#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define UPLOAD_DIR "uploads/"
#define FILE_SIZE_LIMIT (1024 * 1024) // 1MB limit

void handle_upload(const char* file_path, const char* content_type, const char* data) {
    if (strncmp(content_type, "application/pdf", 15)) {
        fprintf(stderr, "Unsupported file type\n");
        return;
    }

    struct stat st = {0};
    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0755);
    }

    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%s", UPLOAD_DIR, file_path);

    int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to open file");
        return;
    }

    ssize_t bytes_written = write(fd, data, strlen(data));
    close(fd);

    if (bytes_written != strlen(data)) {
        fprintf(stderr, "Error writing to file\n");
        remove(full_path);
    } else {
        printf("File uploaded successfully: %s\n", full_path);
    }
}

int main() {
    const char* file_path = "example.pdf";
    const char* content_type = "application/pdf";
    const char* data = "%PDF-1.4\n%...\n"; // Example PDF data

    handle_upload(file_path, content_type, data);

    return 0;
}