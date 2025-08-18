#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void extract_tar(const char *filename, const char *destination) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct tar *t = tar_open_fd(fd, NULL, 0);
    if (!t) {
        perror("tar_open_fd");
        close(fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        struct tar_header th;
        int ret = tar_read_header(t, &th);
        if (ret == TAR_EOF)
            break;
        else if (ret != 0) {
            fprintf(stderr, "Error reading header\n");
            tar_close(t);
            close(fd);
            exit(EXIT_FAILURE);
        }

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", destination, th.name);

        if (S_ISDIR(th.mode)) {
            mkdir(path, th.mode & 0777);
        } else {
            int out_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, th.mode & 0777);
            if (out_fd == -1) {
                perror("open");
                tar_close(t);
                close(fd);
                exit(EXIT_FAILURE);
            }

            ssize_t bytes;
            char buffer[4096];
            while ((bytes = tar_read_data_block(t, buffer, sizeof(buffer))) > 0) {
                if (write(out_fd, buffer, bytes) != bytes) {
                    perror("write");
                    close(out_fd);
                    tar_close(t);
                    close(fd);
                    exit(EXIT_FAILURE);
                }
            }

            close(out_fd);
        }

        if (ret == TAR_ERR)
            break;
    }

    tar_close(t);
    close(fd);
}

int main() {
    const char *tarfile = "archive.tar.gz";
    const char *destination = "/tmp/unpack";

    mkdir(destination, 0755);

    extract_tar(tarfile, destination);

    return 0;
}