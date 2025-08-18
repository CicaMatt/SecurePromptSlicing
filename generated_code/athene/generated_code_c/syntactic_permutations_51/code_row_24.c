#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *filename) {
    struct archive *a;
    struct archive *ext;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_OWNER | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_TIME);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename(%s) failed.\n", filename);
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char dest[1024];
        snprintf(dest, sizeof(dest), "/tmp/unpack/%s", name);
        archive_entry_set_pathname(entry, dest);

        if ((r = archive_write_header(ext, entry)) != ARCHIVE_OK) {
            fprintf(stderr, "archive_write_header() failed.\n");
            exit(1);
        }

        const void *buff;
        size_t size;
        off_t offset;
        while (1 == archive_read_data_block(a, &buff, &size, &offset)) {
            if (archive_write_data_block(ext, buff, size, offset) != ARCHIVE_OK) {
                fprintf(stderr, "archive_write_data_block() failed.\n");
                exit(1);
            }
        }

        if (r != ARCHIVE_EOF && r != ARCHIVE_OK) {
            fprintf(stderr, "archive_read_next_header() failed.\n");
            exit(1);
        }
    }

    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return 1;
    }
    extract_tar(argv[1]);
    return 0;
}