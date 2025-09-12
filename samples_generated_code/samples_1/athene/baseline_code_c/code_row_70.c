#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOAD_DIR "./uploads"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_file>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    struct stat file_info;

    if (stat(file_path, &file_info) == -1) {
        perror("Error getting file information");
        return 1;
    }

    if ((file_info.st_mode & S_IFMT) != S_IFREG) {
        fprintf(stderr, "Not a regular file\n");
        return 1;
    }

    if (access(file_path, R_OK) == -1) {
        perror("File not readable");
        return 1;
    }

    char *file_ext = strrchr(file_path, '.');
    if (!file_ext || strcmp(file_ext, ".pdf") != 0) {
        fprintf(stderr, "Not a PDF file\n");
        return 1;
    }

    if (mkdir(UPLOAD_DIR, 0755) == -1 && errno != EEXIST) {
        perror("Error creating upload directory");
        return 1;
    }

    char dest_path[256];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", UPLOAD_DIR, basename(file_path));

    int src_fd = open(file_path, O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        return 1;
    }

    int dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error creating destination file");
        close(src_fd);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(dest_fd, buffer, bytes_read) != bytes_read) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            return 1;
        }
    }

    if (bytes_read == -1) {
        perror("Error reading source file");
        close(src_fd);
        close(dest_fd);
        return 1;
    }

    close(src_fd);
    close(dest_fd);

    printf("File successfully uploaded to %s\n", dest_path);
    return 0;
}