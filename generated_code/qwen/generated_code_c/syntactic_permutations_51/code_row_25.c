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
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename() failed: %s\n", archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        size_t name_len = strlen(name);
        char out_path[256];

        if (name_len > sizeof(out_path) - 7) { // Subtracting the length of "/tmp/unpack/" and null terminator
            fprintf(stderr, "Path too long: %s\n", name);
            continue;
        }

        snprintf(out_path, sizeof(out_path), "/tmp/unpack/%s", name);

        if (mkdir_p(out_path)) {
            FILE *out = fopen(out_path, "wb");
            if (!out) {
                fprintf(stderr, "Could not open file %s\n", out_path);
                continue;
            }

            const void *buff;
            size_t size;
            la_int64_t offset;

            while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
                fwrite(buff, 1, size, out);
            }

            fclose(out);
        }

        archive_read_data_skip(a);
    }

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "archive_read_next_header() failed: %s\n", archive_error_string(a));
        exit(1);
    }

    archive_read_free(a);
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

    memcpy(tmp, path, len + 1);

    for (p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            mkdir(tmp, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            *p = '/';
        }
    }

    return mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        exit(1);
    }

    extract_tar(argv[1]);

    return 0;
}