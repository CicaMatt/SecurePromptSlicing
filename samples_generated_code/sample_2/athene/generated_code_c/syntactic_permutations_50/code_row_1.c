#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r, n;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if (archive_read_open_filename(a, filename, 10240)) {
        while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
            const char *name = archive_entry_pathname(entry);
            r = archive_read_data_into_fd(a, open(name, O_WRONLY | O_CREAT | O_TRUNC, archive_entry_mode(entry) & 0777));
            if (r != ARCHIVE_OK) {
                fprintf(stderr, "Error extracting file %s: %s\n", name, archive_error_string(a));
                return 1;
            }
        }
    } else {
        fprintf(stderr, "Failed to open archive: %s\n", filename);
        return 1;
    }

    r = archive_read_free(a);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "Error closing archive: %s\n", archive_error_string(a));
        return 1;
    }
    return 0;
}

int main() {
    const char *filename = "archive.zip";
    return extract_tar(filename);
}