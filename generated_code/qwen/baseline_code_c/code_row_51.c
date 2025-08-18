#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>

void extract_tar(const char *filename, const char *destination) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_gzip(a);
    archive_read_support_format_tar(a);

    if ((r = archive_read_open_FILE(a, f)) != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        size_t len = strlen(name);

        if (len > 0 && name[len - 1] != '/') { // not a directory
            char outpath[PATH_MAX];
            snprintf(outpath, sizeof(outpath), "%s/%s", destination, name);

            FILE *out = fopen(outpath, "wb");
            if (!out) {
                perror("Failed to create file");
                archive_read_free(a);
                exit(EXIT_FAILURE);
            }

            const void *buffer;
            size_t size;
            la_int64_t offset;

            while (archive_read_data_block(a, &buffer, &size, &offset) == ARCHIVE_OK) {
                fwrite(buffer, 1, size, out);
            }
            fclose(out);
        }
    }

    if ((r = archive_read_free(a)) != ARCHIVE_OK)
        fprintf(stderr, "%s\n", archive_error_string(a));

    fclose(f);
}

int main() {
    const char *tarfile = "example.tar.gz";
    const char *destination = "/tmp/unpack";

    extract_tar(tarfile, destination);

    return 0;
}