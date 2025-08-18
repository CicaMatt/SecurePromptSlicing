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
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    r = archive_read_open_filename(a, "archive.zip", 10240);
    if (r != ARCHIVE_OK)
        exit(1);

    for (;;) {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;
        if (r < ARCHIVE_OK)
            fprintf(stderr, "%s\n", archive_error_string(a));
        if (r < ARCHIVE_WARN)
            exit(1);

        const char *filename = archive_entry_pathname(entry);
        FILE *fdout = fopen(filename, "wb");
        if (!fdout) {
            fprintf(stderr, "Could not open file %s for writing\n", filename);
            continue;
        }

        const void *buffer;
        size_t size;
        la_int64_t offset;

        while (archive_read_data_block(a, &buffer, &size, &offset) == ARCHIVE_OK)
            fwrite(buffer, 1, size, fdout);

        fclose(fdout);
    }

    archive_read_free(a);

    return 0;
}