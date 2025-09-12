#include <stdio.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>

int main() {
    struct archive *a;
    struct archive *ext;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if ((r = archive_read_open_filename(a, "archive.zip", 10240))) {
        fprintf(stderr, "Archive open error: %s\n", archive_error_string(a));
        return 1;
    }

    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_FFLAGS);

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        r = archive_write_header(ext, entry);
        if (r != ARCHIVE_OK)
            fprintf(stderr, "Error extracting file header: %s\n", archive_error_string(ext));
        else {
            const void *buff;
            size_t size;
            off_t offset;

            while ((r = archive_read_data_block(a, &buff, &size, &offset)) == ARCHIVE_OK) {
                if (archive_write_data_block(ext, buff, size, offset) != ARCHIVE_OK)
                    fprintf(stderr, "Error writing data block: %s\n", archive_error_string(ext));
            }
            if (r != ARCHIVE_EOF) {
                fprintf(stderr, "Error reading data block: %s\n", archive_error_string(a));
            } else {
                r = archive_write_finish_entry(ext);
                if (r != ARCHIVE_OK)
                    fprintf(stderr, "Error finalizing file extraction: %s\n", archive_error_string(ext));
            }
        }
    }

    archive_read_free(a);
    archive_write_disk_free(ext);

    return 0;
}