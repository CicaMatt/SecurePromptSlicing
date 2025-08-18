#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <zlib.h>
#include <bzlib.h>

void extract_tar(const char *path, const char *dest) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    struct archive *a;
    struct archive_entry *entry;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if (archive_read_open_FILE(a, file) != ARCHIVE_OK) {
        fprintf(stderr, "Failed to open tar archive\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        int r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF) break;
        if (r < ARCHIVE_OK) {
            fprintf(stderr, "Error reading header: %s\n", archive_error_string(a));
            exit(EXIT_FAILURE);
        }

        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dest, archive_entry_pathname(entry));

        if (archive_entry_filetype(entry) == S_IFDIR) {
            mkdir(fullpath, 0755);
        } else {
            FILE *out = fopen(fullpath, "wb");
            if (!out) {
                fprintf(stderr, "Failed to create file %s\n", fullpath);
                exit(EXIT_FAILURE);
            }

            const void *buff;
            size_t size;
            off_t offset;

            while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
                if (fwrite(buff, 1, size, out) != size) {
                    fprintf(stderr, "Write error\n");
                    exit(EXIT_FAILURE);
                }
            }

            fclose(out);
        }
    }

    archive_read_free(a);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    extract_tar(argv[1], "/tmp/unpack");

    return 0;
}