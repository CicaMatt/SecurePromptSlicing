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
    archive_read_support_format_zip(a);
    archive_read_support_filter_all(a);

    r = archive_read_open_filename(a, "archive.zip", 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        return 1;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char outpath[256];
        snprintf(outpath, sizeof(outpath), "/tmp/unpack/%s", name);

        if (mkdir_p(outpath, 0755)) {
            fprintf(stderr, "Failed to create directory for %s\n", outpath);
            continue;
        }

        FILE *out = fopen(outpath, "wb");
        if (!out) {
            fprintf(stderr, "Could not open output file: %s\n", outpath);
            continue;
        }

        const void *buffer;
        size_t size;
        int64_t offset;

        while (archive_read_data_block(a, &buffer, &size, &offset) == ARCHIVE_OK)
            fwrite(buffer, 1, size, out);

        fclose(out);
    }

    archive_read_close(a);
    archive_read_free(a);

    return 0;
}

int mkdir_p(const char *path, mode_t mode) {
    char tmp[256];
    char *p = NULL;
    size_t len;

    snprintf(tmp, sizeof(tmp), "%s", path);
    len = strlen(tmp);
    if (tmp[len - 1] == '/')
        tmp[len - 1] = '\0';
    for (p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            mkdir(tmp, mode);
            *p = '/';
        }
    }
    return mkdir(tmp, mode);
}