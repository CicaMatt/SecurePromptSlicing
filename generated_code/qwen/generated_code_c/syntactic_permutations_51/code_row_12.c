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
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "%s: %s\n", filename, archive_error_string(a));
        exit(1);
    }
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        FILE *out = fopen(name, "wb");
        if (!out) {
            fprintf(stderr, "Could not open %s for writing\n", name);
            continue;
        }
        size_t len;
        const void *buf;
        while (archive_read_data_block(a, &buf, &len, NULL) == ARCHIVE_OK)
            fwrite(buf, 1, len, out);
        fclose(out);
    }
    archive_read_free(a);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    extract_tar(argv[1]);

    return EXIT_SUCCESS;
}