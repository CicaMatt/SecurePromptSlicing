#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOAD_DIR "uploads"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf-file>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    char dest_path[256];

    if (mkdir(UPLOAD_DIR, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1 && errno != EEXIST) {
        perror("Error creating uploads directory");
        return 1;
    }

    snprintf(dest_path, sizeof(dest_path), "%s/%s", UPLOAD_DIR, strrchr(file_path, '/') ? strrchr(file_path, '/') + 1 : file_path);

    int src_fd = open(file_path, O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        return 1;
    }

    int dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (dest_fd == -1) {
        close(src_fd);
        perror("Error opening destination file");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        write(dest_fd, buffer, bytes_read);
    }

    close(src_fd);
    close(dest_fd);

    if (bytes_read == -1) {
        perror("Error reading from source file");
        return 1;
    }

    printf("File uploaded successfully to %s\n", dest_path);
    return 0;
}