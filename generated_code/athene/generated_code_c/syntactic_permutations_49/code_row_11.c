#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r, fd;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename() failed: %s\n", archive_error_string(a));
        return 1;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        mode_t mode = archive_entry_mode(entry);

        if ((fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, mode & 0777)) < 0) {
            fprintf(stderr, "open(%s) failed: %s\n", name, strerror(errno));
            return 1;
        }

        while ((r = archive_read_data(a, &buf, sizeof(buf))) > 0) {
            if (write(fd, buf, r) != r) {
                close(fd);
                fprintf(stderr, "write(%s) failed: %s\n", name, strerror(errno));
                return 1;
            }
        }

        if (r != ARCHIVE_EOF) {
            close(fd);
            fprintf(stderr, "archive_read_data() failed: %s\n", archive_error_string(a));
            return 1;
        }

        close(fd);

        if ((mode & S_IFMT) == S_IFDIR) {
            chmod(name, mode | S_IRWXU);
        } else {
            chmod(name, mode);
        }
    }

    r = archive_read_free(a);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "archive_read_free() failed: %s\n", archive_error_string(a));
        return 1;
    }

    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <zipfile>\n", argv[0]);
        return 1;
    }
    return extract(argv[1]);
}


Note: This code requires linking against the `libarchive` library. To compile, use:

gcc -o extract_zip extract_zip.c -larchive