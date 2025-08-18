#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

int main() {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    r = archive_read_open_filename(a, "archive.zip", 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        size_t len = strlen(name);
        char outpath[1024];

        if (len > sizeof(outpath) - 9) { // 9 for "/tmp/unpack/" and null terminator
            fprintf(stderr, "Path too long: %s\n", name);
            continue;
        }

        snprintf(outpath, sizeof(outpath), "/tmp/unpack/%s", name);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            if (mkdir(outpath, 0755) != 0 && errno != EEXIST) {
                fprintf(stderr, "Could not create directory: %s\n", outpath);
            }
        } else {
            FILE *f = fopen(outpath, "wb");
            if (!f) {
                fprintf(stderr, "Could not open file for writing: %s\n", outpath);
                continue;
            }

            const void *buff;
            size_t size;
            off_t offset;

            while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
                fwrite(buff, 1, size, f);
            }
            fclose(f);
        }

        archive_read_data_skip(a);
    }

    if ((r = archive_read_free(a)) != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        exit(1);
    }

    return 0;
}