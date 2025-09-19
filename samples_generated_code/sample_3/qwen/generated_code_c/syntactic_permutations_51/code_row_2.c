#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename() failed: %s\n", archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *path = archive_entry_pathname(entry);
        mode_t mode = archive_entry_mode(entry);

        if (S_ISDIR(mode)) {
            mkdir(path, 0755);
        } else {
            int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
            if (fd < 0) {
                fprintf(stderr, "Could not create file %s\n", path);
                exit(1);
            }
            while ((r = archive_read_data(a, &entry, sizeof(entry))) > 0) {
                write(fd, entry, r);
            }
            close(fd);
        }

        archive_read_data_skip(a);
    }

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "archive_read_next_header() failed: %s\n", archive_error_string(a));
        exit(1);
    }

    archive_read_free(a);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return 1;
    }

    extract_tar(argv[1]);

    return 0;
}