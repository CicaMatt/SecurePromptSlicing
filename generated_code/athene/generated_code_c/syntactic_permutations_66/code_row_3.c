#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOAD_DIR "uploads"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *upload_path = UPLOAD_DIR;

    struct stat st = {0};
    if (stat(upload_path, &st) == -1) {
        mkdir(upload_path, 0700);
    }

    char dest_filename[BUFFER_SIZE];
    snprintf(dest_filename, sizeof(dest_filename), "%s/%s", upload_path, filename);

    int src_fd = open(filename, O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        return 1;
    }

    int dest_fd = open(dest_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error creating destination file");
        close(src_fd);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        write(dest_fd, buffer, bytes_read);
    }

    close(src_fd);
    close(dest_fd);

    printf("File uploaded to %s\n", dest_filename);
    return 0;
}