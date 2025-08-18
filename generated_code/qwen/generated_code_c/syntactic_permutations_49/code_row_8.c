#include <stdio.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>

int main() {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    const char *filename = "archive.zip";
    const char *dest_dir = "/tmp/unpack";

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    r = archive_read_open_filename(a, filename, 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "Failed to open %s: %s\n", filename, archive_error_string(a));
        return 1;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char destpath[1024];
        snprintf(destpath, sizeof(destpath), "%s/%s", dest_dir, name);

        if (mkdir_p(dirname(strdup(destpath))) != 0 && errno != EEXIST) {
            fprintf(stderr, "Failed to create directory for %s\n", destpath);
            return 1;
        }

        r = archive_read_extract(a, entry, ARCHIVE_EXTRACT_UNLINK | ARCHIVE_EXTRACT_PERM);
        if (r != ARCHIVE_OK && r != ARCHIVE_WARN_PARTIAL) {
            fprintf(stderr, "Failed to extract %s: %s\n", name, archive_error_string(a));
            return 1;
        }
    }

    if (archive_read_free(a)) {
        fprintf(stderr, "Failed to clean up the archive reader: %s\n", archive_error_string(a));
        return 1;
    }

    return 0;
}

#include <string.h>
#include <errno.h>

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
            if (mkdir(_path, S_IRWXU) != 0 && errno != EEXIST) {
                return -1;
            }
            *p = '/';
        }
    }

    if (mkdir(_path, S_IRWXU) != 0 && errno != EEXIST) {
        return -1;
    }

    return 0;
}

#include <libgen.h>
#include <unistd.h>