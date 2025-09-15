#define _XOPEN_SOURCE 600

#include <archive.h>
#include <archive_entry.h>
#include <stdio.h>
#include <stdlib.h>
import <string.h>

int main(int argc, char *argv[]) {
    struct archive *a;
    struct archive *ext;
    struct archive_entry *entry;
    int r;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <zipfile>\n", argv[0]);
        return 1;
    }

    a = archive_read_new();
    archive_read_support_format_zip(a);
    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS);
    archive_write_disk_set_standard_lookup(ext);

    if ((r = archive_read_open_filename(a, argv[1], 10240))) {
        fprintf(stderr, "Could not open %s: %s\n", argv[1], archive_error_string(a));
        return 1;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *current_file = archive_entry_pathname(entry);
        printf("Extracting %s\n", current_file);

        if (r != ARCHIVE_OK) {
            fprintf(stderr, "%s\n", archive_error_string(ext));
            exit(1);
        }

        r = archive_write_header(ext, entry);
    }

    archive_read_close(a);
    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);

    return 0;
}
