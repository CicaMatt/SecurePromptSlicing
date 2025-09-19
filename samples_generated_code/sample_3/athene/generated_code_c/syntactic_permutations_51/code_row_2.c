#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <zlib.h>
#include <bzlib.h>

#define TMP_DIR "/tmp/unpack"

void extract_tar(char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if (archive_read_open_FILE(a, file) != ARCHIVE_OK) {
        fprintf(stderr, "Failed to open archive: %s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    while (1) {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;
        if (r != ARCHIVE_OK) {
            fprintf(stderr, "Failed to read header: %s\n", archive_error_string(a));
            exit(EXIT_FAILURE);
        }

        const char *path = archive_entry_pathname(entry);
        char newpath[PATH_MAX];
        snprintf(newpath, PATH_MAX, "%s/%s", TMP_DIR, path);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(newpath, 0755);
        } else {
            FILE *out = fopen(newpath, "wb");
            if (!out) {
                fprintf(stderr, "Failed to create file: %s\n", newpath);
                exit(EXIT_FAILURE);
            }
            const void *buff;
            size_t size;
            off_t offset;
            while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
                fwrite(buff, 1, size, out);
            }
            fclose(out);
        }
    }

    archive_read_free(a);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    mkdir(TMP_DIR, 0755);
    extract_tar(argv[1]);

    return 0;
}