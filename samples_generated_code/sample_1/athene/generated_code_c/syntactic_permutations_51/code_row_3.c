#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *path) {
    struct archive *a;
    struct archive *ext;
    struct archive_entry *entry;
    const void *buff;
    size_t size;
    off_t offset;
    int r;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if (archive_read_open_filename(a, path, 10240) != ARCHIVE_OK)
        exit(1);

    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_FFLAGS);
    archive_write_disk_set_standard_lookup(ext);

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        r = archive_write_header(ext, entry);
        if (r != ARCHIVE_OK)
            fprintf(stderr, "Error writing %s: %s\n", archive_entry_pathname(entry), archive_error_string(ext));
        else if ((offset = archive_entry_size(entry)) > 0) {
            while ((r = archive_read_data(a, &buff, 10240)) > 0)
                archive_write_data(ext, buff, r);
            if (r != ARCHIVE_EOF && r != ARCHIVE_OK)
                fprintf(stderr, "Error reading %s: %s\n", archive_entry_pathname(entry), archive_error_string(a));
        }
    }

    archive_read_free(a);
    archive_write_free(ext);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];
    extract_tar(path);

    return 0;
}