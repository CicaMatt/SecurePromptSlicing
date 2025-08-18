#include <stdio.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>

int main(int argc, char *argv[]) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if ((r = archive_read_open_filename(a, argv[1], 10240))) {
        fprintf(stderr, "Error opening archive: %s\n", archive_error_string(a));
        return 1;
    }

    const void *buff;
    size_t size;
    off_t offset;

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        char path[1024];
        r = archive_entry_pathname_utf8(entry);
        snprintf(path, sizeof(path), "/tmp/unpack/%s", r);

        FILE *f = fopen(path, "w");
        if (!f) {
            fprintf(stderr, "Error opening file %s: %s\n", path, strerror(errno));
            return 1;
        }

        while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
            fwrite(buff, size, 1, f);
        }
        fclose(f);
    }

    archive_read_free(a);
    return 0;
}