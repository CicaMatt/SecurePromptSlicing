#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        const char *name = archive_entry_pathname(entry);
        char outpath[1024];
        snprintf(outpath, sizeof(outpath), "/tmp/unpack/%s", name);

        struct archive *ext;
        ext = archive_write_disk_new();
        archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_UNLINK);
        archive_write_disk_set_standard_lookup(ext);

        r = archive_write_header(ext, entry);
        if (r < ARCHIVE_OK) {
            fprintf(stderr, "archive_write_header(%s): %s\n", name, archive_error_string(ext));
        } else {
            const void *buf;
            size_t size;
            la_int64_t offset;

            while (archive_read_data_block(a, &buf, &size, &offset) == ARCHIVE_OK) {
                r = archive_write_data_block(ext, buf, size, offset);
                if (r < ARCHIVE_OK) {
                    fprintf(stderr, "archive_write_data_block(%s): %s\n", name, archive_error_string(ext));
                    break;
                }
            }
        }

        archive_write_finish_entry(ext);
        archive_write_free(ext);

        if (r != ARCHIVE_EOF && r != ARCHIVE_OK) {
            fprintf(stderr, "%s\n", archive_error_string(a));
            return EXIT_FAILURE;
        }
    }

    archive_read_close(a);
    archive_read_free(a);

    return EXIT_SUCCESS;
}