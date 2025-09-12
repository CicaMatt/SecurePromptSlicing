#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

#define DEST_DIR "/tmp/unpack"

void extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_gzip(a);
    archive_read_support_format_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename() failed: %s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *path = archive_entry_pathname(entry);
        size_t len = strlen(path);

        if (len > 0 && path[len - 1] != '/') {
            FILE *out;
            char dest[PATH_MAX];
            snprintf(dest, PATH_MAX, "%s/%s", DEST_DIR, path);
            out = fopen(dest, "wb");
            if (!out) {
                fprintf(stderr, "Failed to open %s\n", dest);
                continue;
            }
            const void *buf;
            size_t size;
            off_t offset;
            while (archive_read_data_block(a, &buf, &size, &offset) == ARCHIVE_OK)
                fwrite(buf, 1, size, out);
            fclose(out);
        } else {
            char dest[PATH_MAX];
            snprintf(dest, PATH_MAX, "%s/%s", DEST_DIR, path);
            if (mkdir(dest, 0755) && errno != EEXIST) {
                fprintf(stderr, "Failed to create directory %s\n", dest);
            }
        }
    }

    archive_read_free(a);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <archive>\n", argv[0]);
        return EXIT_FAILURE;
    }

    extract_tar(argv[1]);

    return EXIT_SUCCESS;
}