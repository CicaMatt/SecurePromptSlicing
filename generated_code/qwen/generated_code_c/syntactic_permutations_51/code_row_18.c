#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "%s: %s\n", filename, archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        if (mkdir(name, 0755) != 0 && errno != EEXIST) {
            fprintf(stderr, "Could not create directory %s\n", name);
            exit(1);
        }
        FILE *out;
        out = fopen(name, "wb");
        if (!out) {
            fprintf(stderr, "Could not open file %s\n", name);
            exit(1);
        }

        const void *buffer;
        size_t size;
        int64_t offset;

        while (archive_read_data_block(a, &buffer, &size, &offset) == ARCHIVE_OK) {
            fwrite(buffer, 1, size, out);
        }
        fclose(out);

        archive_read_data_skip(a);
    }

    if ((r = archive_read_free(a))) {
        fprintf(stderr, "%s: %s\n", filename, archive_error_string(a));
        exit(1);
    }
}

int main() {
    const char *tarfile = "example.tar.gz"; // Replace with your tar file name
    extract_tar(tarfile);
    return 0;
}