#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

#define OUTPUT_DIR "/tmp/unpack"

void extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_gzip(a);
    archive_read_support_format_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "Failed to open tar file: %s\n", archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char outpath[PATH_MAX];
        snprintf(outpath, sizeof(outpath), "%s/%s", OUTPUT_DIR, name);

        if (mkdir_p(outpath)) {
            fprintf(stderr, "Failed to create directory: %s\n", strerror(errno));
            exit(1);
        }

        FILE *out = fopen(outpath, "wb");
        if (!out) {
            fprintf(stderr, "Failed to open output file: %s\n", strerror(errno));
            exit(1);
        }

        const void *buf;
        size_t size;
        la_int64_t offset;

        while (archive_read_data_block(a, &buf, &size, &offset) == ARCHIVE_OK)
            fwrite(buf, 1, size, out);

        fclose(out);
    }

    archive_read_free(a);
}

int mkdir_p(const char *path) {
    const size_t len = strlen(path);
    char tmp[PATH_MAX];
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
            if (mkdir(tmp, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
                if (errno != EEXIST)
                    return -1;
            }
            *p = '/';
        }
    }

    if (mkdir(tmp, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
        if (errno != EEXIST)
            return -1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        exit(1);
    }

    extract_tar(argv[1]);

    return 0;
}