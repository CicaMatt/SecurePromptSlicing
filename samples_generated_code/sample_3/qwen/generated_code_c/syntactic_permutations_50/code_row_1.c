#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

void extract_files(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "Failed to open file: %s\n", archive_error_string(a));
        goto cleanup;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *path = archive_entry_pathname(entry);
        mode_t mode = archive_entry_mode(entry);

        if (S_ISDIR(mode)) {
            if (mkdir(path, 0755) != 0 && errno != EEXIST) {
                fprintf(stderr, "Failed to create directory: %s\n", path);
                goto cleanup;
            }
        } else if (S_ISREG(mode)) {
            FILE *out = fopen(path, "wb");
            if (!out) {
                fprintf(stderr, "Failed to create file: %s\n", path);
                goto cleanup;
            }

            const void *buffer;
            size_t len;
            int64_t offset;

            while (archive_read_data_block(a, &buffer, &len, &offset) == ARCHIVE_OK)
                fwrite(buffer, 1, len, out);

            fclose(out);
        }
    }

cleanup:
    archive_read_free(a);
}

int main() {
    extract_files("archive.zip");
    return 0;
}