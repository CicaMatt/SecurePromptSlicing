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
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        return EXIT_FAILURE;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *pathname = archive_entry_pathname(entry);
        char destpath[1024];
        snprintf(destpath, sizeof(destpath), "/tmp/unpack/%s", pathname);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir_p(destpath);
        } else {
            FILE *out = fopen(destpath, "wb+");
            if (!out) {
                fprintf(stderr, "Could not open file %s\n", destpath);
                archive_read_free(a);
                return EXIT_FAILURE;
            }
            const void *buffer;
            size_t size;
            off_t offset;

            while (archive_read_data_block(a, &buffer, &size, &offset) == ARCHIVE_OK) {
                fwrite(buffer, 1, size, out);
            }

            fclose(out);
        }

        archive_read_data_skip(a);
    }

    r = archive_read_free(a);
    if (r != ARCHIVE_OK && r != ARCHIVE_EOF) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int mkdir_p(const char *path) {
    const size_t len = strlen(path);
    char tmp[len + 1];
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
            mkdir(tmp, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            *p = '/';
        }
    }

    return mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}