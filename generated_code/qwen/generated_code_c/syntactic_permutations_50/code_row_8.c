#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <archive.h>
#include <archive_entry.h>

int main() {
    struct archive *a;
    struct archive_entry *entry;
    int flags;
    const char *filename;

    // Ensure the target directory exists
    if (mkdir("/tmp/unpack", 0755) != 0 && errno != EEXIST) {
        perror("Failed to create /tmp/unpack");
        return EXIT_FAILURE;
    }

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if (archive_read_open_filename(a, "archive.zip", 10240) != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        archive_read_free(a);
        return EXIT_FAILURE;
    }

    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        filename = archive_entry_pathname(entry);

        if (filename == NULL || *filename == '\0') continue;

        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "/tmp/unpack/%s", filename);

        if (archive_read_extract(a, entry, flags) != ARCHIVE_OK) {
            fprintf(stderr, "%s\n", archive_error_string(a));
            archive_read_free(a);
            return EXIT_FAILURE;
        }
    }

    int r = archive_read_free(a);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        return EXIT_FAILURE;
    }

    return 0;
}