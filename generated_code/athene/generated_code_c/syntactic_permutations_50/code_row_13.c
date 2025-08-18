#include <stdio.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>

int main() {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename(a, "archive.zip", 10240))) {
        fprintf(stderr, "archive_read_open_filename failed: %s\n", archive_error_string(a));
        return 1;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        if ((r = archive_read_extract(a, entry, ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_TIME)) != ARCHIVE_OK) {
            fprintf(stderr, "archive_read_extract failed for %s: %s\n", name, archive_error_string(a));
            return 1;
        }
    }

    r = archive_read_free(a);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "archive_read_free failed: %s\n", archive_error_string(a));
        return 1;
    }

    return 0;
}