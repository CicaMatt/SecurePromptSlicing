#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <zlib.h>
#include <bzlib.h>

#define TARFILE "/path/to/archive.tar.gz"
#define TMPDIR "/tmp/unpack"

void extract_tar(const char *filename, const char *outdir) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    struct archive *a;
    struct archive_entry *entry;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if (archive_read_open_FILE(a, file) != ARCHIVE_OK) {
        fprintf(stderr, "Failed to open tar archive.\n");
        exit(EXIT_FAILURE);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", outdir, name);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(path, 0755);
        } else {
            FILE *out = fopen(path, "wb");
            if (!out) {
                perror("fopen");
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

int main() {
    extract_tar(TARFILE, TMPDIR);
    return 0;
}