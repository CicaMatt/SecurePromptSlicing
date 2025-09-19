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

    const char *filename = "archive.zip";
    const char *destination = "/tmp/unpack/";

    // Ensure the destination directory exists
    if (mkdir(destination, 0755) != 0 && errno != EEXIST) {
        perror("Failed to create destination directory");
        return EXIT_FAILURE;
    }

    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    r = archive_read_open_filename(a, filename, 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "%s: %s\n", archive_error_string(a), filename);
        return EXIT_FAILURE;
    }

    for (;;) {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;
        if (r < ARCHIVE_OK)
            fprintf(stderr, "%s\n", archive_error_string(a));
        else if (r < ARCHIVE_WARN)
            fprintf(stderr, "WARNING: %s\n", archive_error_string(a));

        char outpath[1024];
        snprintf(outpath, sizeof(outpath), "%s%s", destination, archive_entry_pathname(entry));

        r = archive_read_extract(a, entry, flags);
        if (r < ARCHIVE_OK)
            fprintf(stderr, "%s\n", archive_error_string(a));
        else if (r < ARCHIVE_WARN)
            fprintf(stderr, "WARNING: %s\n", archive_error_string(a));
    }

    archive_read_free(a);

    return EXIT_SUCCESS;
}