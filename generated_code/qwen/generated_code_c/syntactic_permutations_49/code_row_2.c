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
        goto cleanup;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *filename = archive_entry_pathname(entry);
        char outpath[1024];
        snprintf(outpath, sizeof(outpath), "/tmp/unpack/%s", filename);

        if (mkdir_parents(outpath)) {
            fprintf(stderr, "Failed to create directory for %s\n", outpath);
            goto cleanup;
        }

        FILE *out = fopen(outpath, "wb");
        if (!out) {
            perror("fopen");
            goto cleanup;
        }

        const void *buffer;
        size_t size;
        la_int64_t offset;
        while (archive_read_data_block(a, &buffer, &size, &offset) == ARCHIVE_OK)
            fwrite(buffer, 1, size, out);

        fclose(out);
    }

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        goto cleanup;
    }

cleanup:
    archive_read_free(a);
    return EXIT_SUCCESS;
}

int mkdir_parents(const char *path) {
    char *buf = strdup(path), *p = buf;
    int res = 0;

    if (*p == '/')
        p++;

    while (1) {
        p = strchr(p, '/');
        if (!p)
            break;
        *p = '\0';
        res = mkdir(buf, 0755);
        *p++ = '/';
    }

    free(buf);
    return res;
}