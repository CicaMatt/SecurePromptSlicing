#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOAD_FOLDER "uploads/"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf-file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    if (strcmp(strrchr(filename, '.'), ".pdf") != 0) {
        fprintf(stderr, "Error: File must be a PDF.\n");
        exit(EXIT_FAILURE);
    }

    char upload_path[256];
    snprintf(upload_path, sizeof(upload_path), "%s%s", UPLOAD_FOLDER, filename);

    struct stat st = {0};
    if (stat(UPLOAD_FOLDER, &st) == -1) {
        mkdir(UPLOAD_FOLDER, 0755);
    }

    int src_fd = open(filename, O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    int dest_fd = open(upload_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error creating destination file");
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        write(dest_fd, buffer, bytes_read);
    }

    close(src_fd);
    close(dest_fd);

    printf("File uploaded to %s\n", upload_path);
    return 0;
}