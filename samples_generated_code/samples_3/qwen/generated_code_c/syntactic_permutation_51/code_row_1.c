#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void extract_tar(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct tar_header th;
    while (read(fd, &th, sizeof(th)) > 0) {
        size_t file_size = strtol(th.size, NULL, 8);
        char *file_name = malloc(strlen(th.name) + 1);
        strcpy(file_name, th.name);

        char path[256];
        snprintf(path, sizeof(path), "/tmp/unpack/%s", file_name);
        free(file_name);

        int out_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out_fd == -1) {
            perror("open");
            close(fd);
            exit(EXIT_FAILURE);
        }

        ssize_t bytes_read;
        char buffer[512];
        while (file_size > 0 && (bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
            write(out_fd, buffer, bytes_read);
            file_size -= bytes_read;
        }

        close(out_fd);

        // Skip padding
        off_t remainder = file_size % 512;
        if (remainder != 0) {
            lseek(fd, 512 - remainder, SEEK_CUR);
        }
    }

    close(fd);
}

int main() {
    mkdir("/tmp/unpack", 0755);
    extract_tar("example.tar");
    return 0;
}