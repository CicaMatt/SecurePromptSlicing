#include <stdio.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if (archive_read_open_filename(a, filename, 10240)) {
        while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
            const char *name = archive_entry_pathname(entry);
            char target[512];
            snprintf(target, sizeof(target), "/tmp/unpack/%s", name);

            if ((r = archive_read_data_into_fd(a, open(target, O_WRONLY | O_CREAT | O_TRUNC, 0644))) != ARCHIVE_OK) {
                fprintf(stderr, "Error extracting %s: %s\n", name, archive_error_string(a));
                exit(1);
            }
        }
    } else {
        fprintf(stderr, "Failed to open %s: %s\n", filename, archive_error_string(a));
        exit(1);
    }

    archive_read_free(a);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return 1;
    }

    extract_tar(argv[1]);

    return 0;
}