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
        return EXIT_FAILURE;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char outpath[1024];
        snprintf(outpath, sizeof(outpath), "/tmp/unpack/%s", name);

        if (mkdir_parents(outpath)) {
            fprintf(stderr, "Could not create directory %s\n", outpath);
            return EXIT_FAILURE;
        }

        FILE *out = fopen(outpath, "wb");
        if (!out) {
            perror("fopen");
            archive_read_free(a);
            return EXIT_FAILURE;
        }

        const void *buf;
        size_t size;
        la_int64_t offset;

        while (archive_read_data_block(a, &buf, &size, &offset) == ARCHIVE_OK)
            fwrite(buf, 1, size, out);

        fclose(out);
    }

    archive_read_free(a);
    return EXIT_SUCCESS;
}

int mkdir_parents(const char *path) {
    char *sep = strchr(path + 1, '/');
    while (sep != NULL) {
        char tmp[1024];
        strncpy(tmp, path, sep - path);
        tmp[sep - path] = '\0';
        if (mkdir(tmp, 0755) && errno != EEXIST)
            return -1;
        sep = strchr(sep + 1, '/');
    }
    return 0;
}