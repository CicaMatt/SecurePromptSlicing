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
    if (r != ARCHIVE_OK)
        return 1;

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char outpath[PATH_MAX];
        snprintf(outpath, sizeof(outpath), "/tmp/unpack/%s", name);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir_p(outpath);
        } else {
            FILE *out = fopen(outpath, "wb+");
            if (!out)
                return 1;

            const void *buffer;
            size_t size;
            la_int64_t offset;

            while (archive_read_data_block(a, &buffer, &size, &offset) == ARCHIVE_OK) {
                fwrite(buffer, 1, size, out);
            }

            fclose(out);
        }
    }

    archive_read_free(a);
    return 0;
}

int mkdir_p(const char *path) {
    const char *sep = strrchr(path, '/');
    if (sep != NULL && sep != path) {
        char parent[PATH_MAX];
        strncpy(parent, path, sep - path);
        parent[sep - path] = '\0';
        mkdir_p(parent);
    }
    return mkdir(path, 0755);
}