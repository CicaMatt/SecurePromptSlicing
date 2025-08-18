#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <utime.h>

void extract_tar_gz(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int fd;
    struct stat st;

    tar_t *tar = tar_open(fp, TAR_GNUTAR);
    if (!tar) {
        perror("Error opening tar archive");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    while (1) {
        tar_header_t th;
        int ret = tar_read(tar, &th);
        if (ret == TAR_EOF) break;
        if (ret < 0) {
            perror("Error reading tar header");
            tar_close(tar);
            fclose(fp);
            exit(EXIT_FAILURE);
        }

        char path[1024];
        snprintf(path, sizeof(path), "/tmp/unpack/%s", th.name);

        switch (th.typeflag) {
            case TAR_NORMAL:
                fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) {
                    perror("Error creating file");
                    tar_close(tar);
                    fclose(fp);
                    exit(EXIT_FAILURE);
                }

                char buffer[8192];
                ssize_t bytes_read;
                while ((bytes_read = tar_block_read(tar, buffer, sizeof(buffer))) > 0) {
                    if (write(fd, buffer, bytes_read) != bytes_read) {
                        perror("Error writing to file");
                        close(fd);
                        tar_close(tar);
                        fclose(fp);
                        exit(EXIT_FAILURE);
                    }
                }
                close(fd);

                if (bytes_read < 0) {
                    perror("Error reading block from tar archive");
                    tar_close(tar);
                    fclose(fp);
                    exit(EXIT_FAILURE);
                }

                utime(path, &th.mtime);
                break;

            case TAR_DIRECTORY:
                mkdir(path, th.mode);
                break;
        }
    }

    tar_close(tar);
    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tar.gz file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    extract_tar_gz(argv[1]);

    return EXIT_SUCCESS;
}