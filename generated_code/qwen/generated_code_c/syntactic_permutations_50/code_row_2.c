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
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        return 1;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char path[256];
        snprintf(path, sizeof(path), "/tmp/unpack/%s", name);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            if (mkdir(path, 0755) != 0 && errno != EEXIST) {
                fprintf(stderr, "Could not create directory: %s\n", path);
                return 1;
            }
        } else {
            FILE *out = fopen(path, "wb");
            if (!out) {
                fprintf(stderr, "Could not open file for writing: %s\n", path);
                return 1;
            }

            const void *buffer;
            size_t size;
            int64_t offset;

            while (archive_read_data_block(a, &buffer, &size, &offset) == ARCHIVE_OK)
                fwrite(buffer, size, 1, out);

            fclose(out);
        }

        archive_read_data_skip(a);
    }

    r = archive_read_free(a);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        return 1;
    }

    return 0;
}