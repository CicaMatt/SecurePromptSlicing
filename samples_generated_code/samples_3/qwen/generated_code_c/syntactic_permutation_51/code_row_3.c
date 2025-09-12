#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <fcntl.h>
#include <unistd.h>

void extract_tar(const char *filename, const char *output_dir) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_tar(a);
    archive_read_support_filter_gzip(a);
    archive_read_support_filter_bzip2(a);

    r = archive_read_open_fd(a, fd, 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        char outpath[1024];
        snprintf(outpath, sizeof(outpath), "%s/%s", output_dir, archive_entry_pathname(entry));

        if (S_ISDIR(archive_entry_mode(entry))) {
            mkdir(outpath, 0755);
        } else {
            int ofd = open(outpath, O_WRONLY | O_CREAT | O_TRUNC, archive_entry_mode(entry));
            if (ofd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }

            const void *buffer;
            size_t size;
            la_int64_t offset;

            while (archive_read_data_block(a, &buffer, &size, &offset) == ARCHIVE_OK) {
                write(ofd, buffer, size);
            }
            close(ofd);
        }
    }

    archive_read_free(a);
    close(fd);
}

int main() {
    const char *tarfile = "example.tar.gz";
    const char *output_dir = "/tmp/unpack";

    mkdir(output_dir, 0755);
    extract_tar(tarfile, output_dir);

    return 0;
}