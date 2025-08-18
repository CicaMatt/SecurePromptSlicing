#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_archive(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r, fd;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename() failed: %s\n", archive_error_string(a));
        return r;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        mode_t mode = archive_entry_mode(entry);

        if ((fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, mode)) < 0) {
            fprintf(stderr, "open() failed for %s: %s\n", name, strerror(errno));
            return -1;
        }

        while (1) {
            const void *buff;
            size_t size;
            off_t offset;

            r = archive_read_data_block(a, &buff, &size, &offset);
            if (r == ARCHIVE_EOF)
                break;
            if (r != ARCHIVE_OK) {
                fprintf(stderr, "archive_read_data_block() failed: %s\n", archive_error_string(a));
                return -1;
            }

            if ((r = write(fd, buff, size)) < 0) {
                fprintf(stderr, "write() failed for %s: %s\n", name, strerror(errno));
                close(fd);
                return -1;
            }
        }

        close(fd);

        r = chmod(name, mode);
        if (r != 0) {
            fprintf(stderr, "chmod() failed for %s: %s\n", name, strerror(errno));
            return -1;
        }
    }

    archive_read_free(a);
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <archive.zip>\n", argv[0]);
        return 1;
    }

    return extract_archive(argv[1]);
}