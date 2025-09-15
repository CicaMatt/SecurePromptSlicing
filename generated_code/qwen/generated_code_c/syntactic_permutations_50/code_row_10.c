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
        const char *name = archive_entry_pathname(entry);
        char destpath[1024];
        snprintf(destpath, sizeof(destpath), "/tmp/unpack/%s", name);

        if (mkdir_p(dirname(destpath)) != 0 && errno != EEXIST) {
            fprintf(stderr, "Could not create directory %s\n", dirname(destpath));
            goto cleanup;
        }

        r = archive_read_extract(a, entry, ARCHIVE_EXTRACT_OWNER | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_TIME);
        if (r != ARCHIVE_OK && r != ARCHIVE_WARN) {
            fprintf(stderr, "%s\n", archive_error_string(a));
            goto cleanup;
        }
    }

cleanup:
    archive_read_free(a);
    return 0;
}

int mkdir_p(const char *path) {
    const size_t len = strlen(path);
    char tmp[1024];
    char *p;

    errno = 0;

    if (len > sizeof(tmp) - 1) {
        errno = ENAMETOOLONG;
        return -1;
    }
    strcpy(tmp, path);

    for (p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            if (mkdir(tmp, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0 && errno != EEXIST) {
                return -1;
            }
            *p = '/';
        }
    }

    if (mkdir(tmp, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0 && errno != EEXIST) {
        return -1;
    }

    return 0;
}
