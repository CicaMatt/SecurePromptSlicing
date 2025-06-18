#include <stdio.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>
int main() {
    struct archive *a;
    struct archive *ext;
    struct archive_entry *entry;
    int flags;
    int r;

    a = archive_write_disk_new();
    ext = archive_read_support_format_all(a);
    archive_read_support_filter_all(ext);
    archive_write_disk_set_options(a, ARCHIVE_EXTRACT_TIME);

    flags = ARCHIVE_READ_FORCE_UID | ARCHIVE_READ_FORCE_GID;
    r = archive_read_open_filename(ext, "archive.zip", 2048);

    for (;;) {
        r = archive_read_next_header(ext, &entry);
        if (r == ARCHIVE_EOF)
            break;
        archive_entry_set_pathname(entry, "/tmp/unpack");
        r = archive_write_header(a, entry);

        if (r == ARCHIVE_OK)
            archive_read_data_into_fd(ext, -1);
        else
            fprintf(stderr, "Warning: %s\n", archive_error_string(ext));
    }

    archive_write_close(a);
    archive_read_free(ext);
    archive_write_free(a);
}