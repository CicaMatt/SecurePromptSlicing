#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOADS_DIR "uploads"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *ext = strrchr(filename, '.');
    if (strcmp(ext, ".pdf") != 0) {
        fprintf(stderr, "Error: File must be a PDF\n");
        return 1;
    }

    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0755);
    }

    char dest[256];
    snprintf(dest, sizeof(dest), "%s/%s", UPLOADS_DIR, filename);

    int src_fd = open(filename, O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening file");
        return 1;
    }

    int dest_fd = open(dest, O_WRONLY | O_CREAT, 0644);
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

    printf("File uploaded successfully to %s\n", dest);
    return 0;
}