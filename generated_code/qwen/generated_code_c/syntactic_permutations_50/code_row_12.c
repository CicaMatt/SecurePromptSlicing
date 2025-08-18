#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

int copy_data(struct archive *ar, struct archive *aw) {
    int r;
    const void *buff;
    size_t size;
    la_int64_t offset;

    for (;;) {
        r = archive_read_data_block(ar, &buff, &size, &offset);
        if (r == ARCHIVE_EOF)
            return (ARCHIVE_OK);
        if (r != ARCHIVE_OK)
            return (r);
        r = archive_write_data_block(aw, buff, size, offset);
        if (r != ARCHIVE_OK) {
            fprintf(stderr, "%s\n", archive_error_string(aw));
            return (r);
        }
    }
}

int main(void) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if ((r = archive_read_open_filename(a, "archive.zip", 10240))) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        goto cleanup;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        r = copy_data(a, NULL);
        if (r != ARCHIVE_OK)
            break;
    }

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "%s\n", archive_error_string(a));
    }

cleanup:
    archive_read_free(a);

    return (0);
}