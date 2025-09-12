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

    r = archive_read_open_filename(a, "archive.zip", 10240);
    if (r != ARCHIVE_OK)
        goto cleanup;

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char dest[1024];
        snprintf(dest, sizeof(dest), "/tmp/unpack/%s", name);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir_p(dest);
        } else {
            FILE *out = fopen(dest, "wb+");
            size_t bytes_read;
            const void *buffer;

            while ((bytes_read = archive_read_data_block(a, &buffer, NULL, NULL)) > 0)
                fwrite(buffer, 1, bytes_read, out);

            fclose(out);
        }

        archive_read_data_skip(a);
    }

cleanup:
    archive_read_free(a);
    return (r == ARCHIVE_OK) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int mkdir_p(const char *path) {
    const size_t len = strlen(path);
    char _path[1024];
    char *p;

    errno = 0;

    if (len > sizeof(_path)-1) {
        errno = ENAMETOOLONG;
        return -1;
    }
    strcpy(_path, path);

    for (p = _path + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            mkdir(_path, S_IRWXU);
            *p = '/';
        }
    }

    mkdir(_path, S_IRWXU);
    return 0;
}