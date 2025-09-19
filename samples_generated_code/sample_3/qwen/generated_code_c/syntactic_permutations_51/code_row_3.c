#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar_gz(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_gzip(a);
    archive_read_support_format_all(a);
    r = archive_read_open_filename(a, filename, 10240);

    if (r != ARCHIVE_OK) {
        fprintf(stderr, "Failed to open tar.gz file: %s\n", archive_error_string(a));
        goto cleanup;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        FILE *f = fopen(name, "wb");
        if (!f) {
            fprintf(stderr, "Failed to open file for writing: %s\n", name);
            continue;
        }

        size_t sz;
        const void *buf;
        while (archive_read_data_block(a, &buf, &sz, NULL) == ARCHIVE_OK) {
            fwrite(buf, 1, sz, f);
        }
        fclose(f);
        archive_read_data_skip(a);
    }

cleanup:
    archive_read_free(a);
}

int main() {
    const char *tar_gz_file = "archive.tar.gz";
    extract_tar_gz(tar_gz_file);
    return 0;
}