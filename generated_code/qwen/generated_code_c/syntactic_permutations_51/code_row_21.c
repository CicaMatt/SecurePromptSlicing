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
        perror("Failed to open tar file");
        exit(EXIT_FAILURE);
    }

    struct archive *a;
    struct archive_entry *entry;

    a = archive_read_new();
    archive_read_support_filter_gzip(a);
    archive_read_support_format_tar(a);

    int r = archive_read_open_fd(a, fd, 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *path = archive_entry_pathname(entry);
        mode_t mode = archive_entry_mode(entry);

        if (S_ISDIR(mode)) {
            if (mkdir(path, mode) != 0 && errno != EEXIST) {
                fprintf(stderr, "Failed to create directory: %s\n", path);
                exit(EXIT_FAILURE);
            }
        } else {
            int ofd = open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
            if (ofd == -1) {
                perror("Failed to open file for writing");
                exit(EXIT_FAILURE);
            }

            const void *buffer;
            size_t size;
            la_int64_t offset;

            while (archive_read_data_block(a, &buffer, &size, &offset) == ARCHIVE_OK) {
                if (write(ofd, buffer, size) != size) {
                    perror("Failed to write file");
                    exit(EXIT_FAILURE);
                }
            }

            close(ofd);
        }

        archive_read_data_skip(a);
    }

    archive_read_free(a);
    close(fd);

    if (r == ARCHIVE_FATAL) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }
}

int main() {
    extract_tar("example.tar.gz");
    return 0;
}