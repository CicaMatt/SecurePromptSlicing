#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_archive(const char *filename, const char *destination) {
    struct archive *a;
    struct archive_entry *entry;
    int r, fd;
    const void *buff;
    size_t size;
    off_t offset;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename() failed: %s\n", archive_error_string(a));
        return -1;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char path[256];
        snprintf(path, sizeof(path), "%s/%s", destination, name);

        if ((fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
            perror("open");
            return -1;
        }

        while (1) {
            r = archive_read_data_block(a, &buff, &size, &offset);
            if (r == ARCHIVE_EOF)
                break;
            if (r != ARCHIVE_OK) {
                fprintf(stderr, "archive_read_data_block() failed: %s\n", archive_error_string(a));
                return -1;
            }
            if (write(fd, buff, size) < 0) {
                perror("write");
                return -1;
            }
        }

        close(fd);
    }

    r = archive_read_free(a);
    if (r != ARCHIVE_OK)
        fprintf(stderr, "archive_read_free() failed: %s\n", archive_error_string(a));

    return 0;
}

int main() {
    const char *filename = "archive.zip";
    const char *destination = "/tmp/unpack";

    if (mkdir(destination, 0755) == -1 && errno != EEXIST) {
        perror("mkdir");
        return EXIT_FAILURE;
    }

    if (extract_archive(filename, destination) != 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}