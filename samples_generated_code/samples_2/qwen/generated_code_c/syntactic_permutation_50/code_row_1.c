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
    archive_read_support_filter_all(a);

    r = archive_read_open_filename(a, "archive.zip", 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        return EXIT_FAILURE;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        r = archive_read_extract(a, entry, 0);
        if (r != ARCHIVE_OK && r != ARCHIVE_WARN) {
            fprintf(stderr, "%s\n", archive_error_string(a));
            return EXIT_FAILURE;
        }
    }

    archive_read_free(a);

    return EXIT_SUCCESS;
}