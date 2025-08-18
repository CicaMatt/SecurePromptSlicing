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
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if ((r = archive_read_open_filename(a, "archive.zip", 10240)) != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        return 1;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *path = archive_entry_pathname(entry);
        char out_path[256];
        snprintf(out_path, sizeof(out_path), "/tmp/unpack/%s", path);

        if (mkdir_parents(out_path)) {
            fprintf(stderr, "Failed to create directory for %s\n", out_path);
            return 1;
        }

        FILE *out = fopen(out_path, "wb");
        if (!out) {
            fprintf(stderr, "Could not open file %s for writing\n", out_path);
            continue;
        }

        const void *buffer;
        size_t size;
        int64_t offset;

        while (archive_read_data_block(a, &buffer, &size, &offset) == ARCHIVE_OK)
            fwrite(buffer, 1, size, out);

        fclose(out);
    }

    archive_read_free(a);
    return 0;
}

int mkdir_parents(char *path) {
    char *p = path;

    while ((p = strchr(p + 1, '/'))) {
        *p = '\0';
        if (mkdir(path, 0755) && errno != EEXIST) {
            *p = '/';
            return -1;
        }
        *p = '/';
    }

    return 0;
}