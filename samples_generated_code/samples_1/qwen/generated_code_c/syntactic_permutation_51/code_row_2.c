#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_gzip(a);
    archive_read_support_format_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename() failed: %s\n", archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *path = archive_entry_pathname(entry);
        char outpath[256];
        snprintf(outpath, sizeof(outpath), "/tmp/unpack/%s", path);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir_p(outpath);
        } else {
            FILE *out = fopen(outpath, "wb+");
            if (!out) {
                fprintf(stderr, "Failed to create file: %s\n", outpath);
                continue;
            }
            const void *buffer;
            size_t size;
            int64_t offset;

            while (archive_read_data_block(a, &buffer, &size, &offset) == ARCHIVE_OK) {
                fwrite(buffer, 1, size, out);
            }
            fclose(out);
        }
        archive_read_data_skip(a);
    }

    if ((r = archive_read_free(a)) != ARCHIVE_OK)
        fprintf(stderr, "archive_read_free() failed: %s\n", archive_error_string(a));
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
            if (mkdir(_path, S_IRWXU) != 0 && errno != EEXIST)
                return -1;
            *p = '/';
        }
    }

    if (mkdir(_path, S_IRWXU) != 0 && errno != EEXIST)
        return -1;

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return 1;
    }
    extract_tar(argv[1]);
    return 0;
}