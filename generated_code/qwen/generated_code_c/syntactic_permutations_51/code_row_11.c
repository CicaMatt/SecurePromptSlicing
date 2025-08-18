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
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "%s: %s\n", filename, archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char outpath[1024];
        snprintf(outpath, sizeof(outpath), "/tmp/unpack/%s", name);

        if (mkdir_p(outpath)) {
            fprintf(stderr, "Failed to create directory for %s\n", outpath);
            exit(1);
        }

        FILE *out = fopen(outpath, "wb");
        if (!out) {
            fprintf(stderr, "Could not open %s for writing\n", outpath);
            exit(1);
        }

        const void *buf;
        size_t size;
        la_int64_t offset;

        while (archive_read_data_block(a, &buf, &size, &offset) == ARCHIVE_OK)
            fwrite(buf, 1, size, out);

        fclose(out);
    }

    if ((r = archive_read_free(a))) {
        fprintf(stderr, "Failed to close the archive: %s\n", archive_error_string(a));
        exit(1);
    }
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
            if (mkdir(tmp, S_IRWXU)) {
                if (errno != EEXIST)
                    return -1;
            }
            *p = '/';
        }
    }

    if (mkdir(tmp, S_IRWXU) && errno != EEXIST)
        return -1;

    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return 1;
    }

    extract_tar(argv[1]);

    return 0;
}