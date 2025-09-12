#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *filename, const char *destination) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename() failed: %s\n", archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char destpath[1024];
        snprintf(destpath, sizeof(destpath), "%s/%s", destination, name);

        if (mkdir_p(destpath)) {
            fprintf(stderr, "Could not create directory: %s\n", destpath);
            exit(1);
        }

        FILE *out;
        out = fopen(destpath, "wb+");
        if (!out) {
            fprintf(stderr, "Could not open file for writing: %s\n", destpath);
            exit(1);
        }

        const void *buffer;
        size_t size;
        la_int64_t offset;

        while (archive_read_data_block(a, &buffer, &size, &offset) == ARCHIVE_OK) {
            fwrite(buffer, 1, size, out);
        }

        fclose(out);

        archive_entry_clear(entry);
    }

    if ((r = archive_read_free(a))) {
        fprintf(stderr, "archive_read_free() failed: %s\n", archive_error_string(a));
        exit(1);
    }
}

int mkdir_p(const char *path) {
    const size_t len = strlen(path);
    char _path[1024];
    char *p;

    errno = 0;
    if (len > sizeof(_path) - 1) {
        errno = ENAMETOOLONG;
        return -1;
    }
    strcpy(_path, path);

    for (p = _path + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            if (mkdir(_path, S_IRWXU) != 0) {
                if (errno != EEXIST)
                    return -1;
            }
            *p = '/';
        }
    }

    if (mkdir(_path, S_IRWXU) != 0) {
        if (errno != EEXIST)
            return -1;
    }

    return 0;
}

int main() {
    const char *tarfile = "example.tar.gz";
    const char *destination = "/tmp/unpack";

    extract_tar(tarfile, destination);

    return 0;
}