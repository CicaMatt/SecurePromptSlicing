#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    char buffer[10240];
    size_t n;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "Failed to open %s: %s\n", filename, archive_error_string(a));
        return r;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        if ((r = archive_read_data_into_buffer(a, buffer, sizeof(buffer), &n))) {
            fprintf(stderr, "Error reading data for %s: %s\n", name, archive_error_string(a));
            return r;
        }
        FILE *f = fopen(name, "wb");
        if (!f) {
            fprintf(stderr, "Failed to open file %s for writing\n", name);
            return 1;
        }
        while (n > 0) {
            fwrite(buffer, 1, n, f);
            r = archive_read_data(a, buffer, sizeof(buffer), &n);
            if (r != ARCHIVE_OK) break;
        }
        fclose(f);
    }

    archive_read_free(a);
    return 0;
}

int main() {
    const char *filename = "archive.zip";
    int result = extract_tar(filename);
    return result;
}