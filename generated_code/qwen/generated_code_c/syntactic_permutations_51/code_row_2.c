#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>
#include <unistd.h>

void extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename() failed: %s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *path = archive_entry_pathname(entry);
        mode_t mode = archive_entry_mode(entry);

        if (S_ISDIR(mode)) {
            mkdir(path, mode);
        } else {
            FILE *f;
            char buf[8192];
            size_t len;

            f = fopen(path, "wb");
            if (!f) {
                perror("Failed to open file for writing");
                exit(EXIT_FAILURE);
            }

            while ((len = archive_read_data(a, buf, sizeof(buf))) > 0) {
                fwrite(buf, 1, len, f);
            }
            fclose(f);
        }
        archive_read_data_skip(a);
    }

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "archive_read_next_header() returned %d: %s\n", r, archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    archive_read_free(a);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    chdir("/tmp/unpack");
    extract_tar(argv[1]);

    return EXIT_SUCCESS;
}