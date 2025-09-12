#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void ensure_directory_exists(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0755);
    }
}

void upload_file(const char *filename) {
    const char *upload_dir = "uploads";
    ensure_directory_exists(upload_dir);

    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/%s", upload_dir, filename);

    int src_fd = open(filename, O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening file");
        return;
    }

    int dest_fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        close(src_fd);
        perror("Error creating destination file");
        return;
    }

    const size_t buffer_size = 4096;
    char buffer[buffer_size];
    ssize_t bytes_read;

    while ((bytes_read = read(src_fd, buffer, buffer_size)) > 0) {
        if (write(dest_fd, buffer, bytes_read) != bytes_read) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            return;
        }
    }

    if (bytes_read == -1) {
        perror("Error reading from source file");
    }

    close(src_fd);
    close(dest_fd);
}