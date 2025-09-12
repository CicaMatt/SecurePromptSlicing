#include <stdio.h>
#include <stdlib.h>
#include <tar.h>
#include <zlib.h>
#include <bzlib.h>

void unpack_tar(const char *path, const char *dir) {
    FILE *file = fopen(path, "rb");
    if (!file) return;

    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_compression_all(a);

    if (archive_read_open_FILE(a, file)) {
        while (1) {
            r = archive_read_next_header(a, &entry);
            if (r == ARCHIVE_EOF)
                break;
            if (r != ARCHIVE_OK)
                continue;

            char *name = archive_entry_pathname(entry);
            char newpath[256];
            snprintf(newpath, 256, "%s/%s", dir, name);
            FILE *f = fopen(newpath, "wb");
            if (!f) continue;

            const void *buff;
            size_t size;
            off_t offset;
            while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
                fwrite(buff, 1, size, f);
            }
            fclose(f);
        }
    }

    archive_read_free(a);
    fclose(file);
}

int main() {
    unpack_tar("/path/to/archive.tar.gz", "/tmp/unpack");
    return 0;
}