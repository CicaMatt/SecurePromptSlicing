#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
#define UPLOAD_DIR "uploads"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_file>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    const char *upload_dir = UPLOAD_DIR;

    struct stat st = {0};
    if (stat(upload_dir, &st) == -1) {
        mkdir(upload_dir, 0700);
    }

    char dest_file[BUFFER_SIZE];
    snprintf(dest_file, sizeof(dest_file), "%s/%s", upload_dir, strrchr(file_path, '/') ? strrchr(file_path, '/') + 1 : file_path);

    int src_fd = open(file_path, O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        return 1;
    }

    int dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(src_fd);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        write(dest_fd, buffer, bytes_read);
    }

    close(src_fd);
    close(dest_fd);

    printf("File uploaded to %s\n", dest_file);

    return 0;
}