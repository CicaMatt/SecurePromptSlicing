#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

#define BUFFER_SIZE 10240

void extract_archive(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if ((r = archive_read_open_filename(a, filename, BUFFER_SIZE)) != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        archive_read_free(a);
        exit(EXIT_FAILURE);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *path = archive_entry_pathname(entry);
        size_t len = strlen(path);

        if (len > 0 && path[len - 1] == '/') {
            char dirpath[256];
            snprintf(dirpath, sizeof(dirpath), "/tmp/unpack%s", path);
            mkdirp(dirpath, 0755);
        } else {
            char filepath[256];
            FILE *out;
            const void *buf;
            size_t size;
            la_int64_t offset;

            snprintf(filepath, sizeof(filepath), "/tmp/unpack%s", path);
            out = fopen(filepath, "wb");

            if (!out) {
                fprintf(stderr, "Could not open file %s\n", filepath);
                continue;
            }

            while (archive_read_data_block(a, &buf, &size, &offset) == ARCHIVE_OK)
                fwrite(buf, 1, size, out);

            fclose(out);
        }
        archive_read_data_skip(a);
    }

    if ((r = archive_read_free(a)) != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }
}

void mkdirp(const char *path, mode_t mode) {
    struct stat st;
    const char *ptr;

    for (ptr = path + 1; *ptr; ptr++) {
        if (*ptr == '/') {
            char tmp[256];
            strncpy(tmp, path, ptr - path);
            tmp[ptr - path] = '\0';
            if (stat(tmp, &st) != 0)
                mkdir(tmp, mode);
        }
    }

    if (stat(path, &st) != 0)
        mkdir(path, mode);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    extract_archive(argv[1]);

    return EXIT_SUCCESS;
}