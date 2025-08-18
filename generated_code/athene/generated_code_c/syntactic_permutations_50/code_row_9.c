#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "Failed to open %s: %s\n", filename, archive_error_string(a));
        return 1;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        mode_t mode = archive_entry_mode(entry);

        if (S_ISDIR(mode)) {
            mkdir(name, mode);
        } else {
            FILE *f;
            f = fopen(name, "w");
            if (!f) {
                fprintf(stderr, "Failed to open %s for writing: %s\n", name, strerror(errno));
                archive_read_free(a);
                return 1;
            }
            while ((r = archive_read_data_into_fd(a, fileno(f))) > 0) {}
            fclose(f);

            if (r != ARCHIVE_EOF) {
                fprintf(stderr, "Failed to extract %s: %s\n", name, archive_error_string(a));
                archive_read_free(a);
                return 1;
            }
        }
    }

    r = archive_read_free(a);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "Error freeing archive: %s\n", archive_error_string(a));
        return 1;
    }

    return 0;
}

int main() {
    const char *filename = "archive.zip";
    return extract_tar(filename);
}