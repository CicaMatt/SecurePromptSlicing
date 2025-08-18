#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

int main() {
    struct archive *a;
    struct archive_entry *entry;
    int flags;
    int r;

    // Ensure the output directory exists
    if (system("mkdir -p /tmp/unpack") != 0) {
        fprintf(stderr, "Failed to create directory\n");
        return EXIT_FAILURE;
    }

    // Initialize the archive read structure
    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    // Open the file
    r = archive_read_open_filename(a, "archive.zip", 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        goto cleanup;
    }

    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL |
            ARCHIVE_EXTRACT_FFLAGS | ARCHIVE_EXTRACT_XATTR;

    // Extract files from the archive
    for (;;) {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;
        if (r < ARCHIVE_OK) {
            fprintf(stderr, "%s\n", archive_error_string(a));
            goto cleanup;
        }
        if (r == ARCHIVE_WARN)
            fprintf(stderr, "%s\n", archive_error_string(a));

        char path[1024];
        snprintf(path, sizeof(path), "/tmp/unpack/%s", archive_entry_pathname(entry));

        r = archive_read_extract(a, entry, flags);
        if (r < ARCHIVE_OK) {
            fprintf(stderr, "%s\n", archive_error_string(a));
        }
        else if (ARCHIVE_WARN == r)
            fprintf(stderr, "%s\n", archive_error_string(a));
    }

cleanup:
    // Clean up
    archive_read_free(a);

    return EXIT_SUCCESS;
}