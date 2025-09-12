#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void extract_tar(const char *filename, const char *destination) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct archive *a;
    struct archive_entry *entry;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if (archive_read_open_fd(a, fd, 4096) != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", destination, name);

        struct stat st;
        if (stat(destination, &st) != 0) {
            mkdir(destination, 0755);
        }

        int ofd = open(fullpath, O_WRONLY | O_CREAT | O_TRUNC, archive_entry_mode(entry));
        if (ofd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        size_t r;
        const void *buffer;
        while ((r = archive_read_data_block(a, &buffer, &size, NULL)) != ARCHIVE_EOF) {
            if (r < 0) {
                fprintf(stderr, "%s\n", archive_error_string(a));
                exit(EXIT_FAILURE);
            }
            write(ofd, buffer, size);
        }

        close(ofd);
    }

    archive_read_free(a);
    close(fd);
}

int main() {
    const char *tarfile = "example.tar.gz";
    const char *destination = "/tmp/unpack";

    extract_tar(tarfile, destination);

    return 0;
}