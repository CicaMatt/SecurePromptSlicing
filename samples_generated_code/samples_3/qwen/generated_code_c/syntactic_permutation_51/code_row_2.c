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
    ssize_t bytes_read;
    while ((bytes_read = read(fd, &th, sizeof(th))) > 0) {
        if (bytes_read != sizeof(th)) {
            fprintf(stderr, "Short read on header\n");
            close(fd);
            exit(EXIT_FAILURE);
        }

        char filename[100];
        strncpy(filename, th.name, sizeof(filename));
        filename[sizeof(filename) - 1] = '\0';

        mode_t file_mode = (mode_t)strtol(th.mode, NULL, 8);

        if (th.typeflag == REGTYPE || th.typeflag == AREGTYPE) {
            int ofd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, file_mode);
            if (ofd == -1) {
                perror("open");
                close(fd);
                exit(EXIT_FAILURE);
            }

            size_t file_size = (size_t)strtol(th.size, NULL, 8);
            char buffer[512];
            while (file_size > 0) {
                ssize_t block_read = read(fd, buffer, sizeof(buffer));
                if (block_read == -1) {
                    perror("read");
                    close(ofd);
                    close(fd);
                    exit(EXIT_FAILURE);
                }
                write(ofd, buffer, file_size < sizeof(buffer) ? file_size : sizeof(buffer));
                file_size -= block_read;
            }

            close(ofd);

            off_t padding = (512 - (file_size % 512)) % 512;
            lseek(fd, padding, SEEK_CUR);
        } else if (th.typeflag == DIRTYPE) {
            mkdir(filename, file_mode);
        }
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    extract_tar(argv[1]);

    return EXIT_SUCCESS;
}