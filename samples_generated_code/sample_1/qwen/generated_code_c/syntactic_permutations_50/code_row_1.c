#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

void extract_archive(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "%s: %s\n", filename, archive_error_string(a));
        goto cleanup;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *path = archive_entry_pathname(entry);
        if (mkdir(path, 0755) != 0 && errno != EEXIST) {
            perror("mkdir");
            goto cleanup;
        }
        FILE *out = fopen(path, "wb+");
        if (!out) {
            fprintf(stderr, "%s: %s\n", path, strerror(errno));
            goto cleanup;
        }

        const void *buffer;
        size_t size;
        la_int64_t offset;

        while (archive_read_data_block(a, &buffer, &size, &offset) == ARCHIVE_OK) {
            if (fwrite(buffer, 1, size, out) != size) {
                fprintf(stderr, "%s: %s\n", path, strerror(errno));
                fclose(out);
                goto cleanup;
            }
        }

        fclose(out);

        r = archive_read_data_skip(a);
        if (r < ARCHIVE_WARN) {
            fprintf(stderr, "%s: %s\n", filename, archive_error_string(a));
            goto cleanup;
        }
    }

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "%s: %s\n", filename, archive_error_string(a));
    }

cleanup:
    archive_read_free(a);
}

int main() {
    extract_archive("archive.zip");
    return 0;
}