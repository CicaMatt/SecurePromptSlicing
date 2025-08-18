#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <fcntl.h>
#include <unistd.h>

void extract_tar(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    r = archive_read_open_fd(a, fd, 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *path = archive_entry_pathname(entry);

        if (mkdir(path, 0755) != 0 && errno != EEXIST) {
            perror("mkdir");
            exit(EXIT_FAILURE);
        }

        int out_fd = openat(AT_FDCWD, path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out_fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        r = archive_read_data_into_fd(a, out_fd);
        close(out_fd);

        if (r != ARCHIVE_OK) {
            fprintf(stderr, "%s\n", archive_error_string(a));
            exit(EXIT_FAILURE);
        }
    }

    r = archive_read_free(a);
    close(fd);

    if (r != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    extract_tar(argv[1]);

    return EXIT_SUCCESS;
}