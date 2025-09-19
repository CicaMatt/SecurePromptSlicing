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
        char outpath[1024];
        snprintf(outpath, sizeof(outpath), "/tmp/unpack/%s", name);

        if (mkdir_p(dirname(strdup(outpath)))) {
            fprintf(stderr, "Could not create directory for %s\n", outpath);
            exit(1);
        }

        FILE *out = fopen(outpath, "wb+");
        if (!out) {
            fprintf(stderr, "Failed to open file %s\n", outpath);
            continue;
        }

        while ((r = archive_read_data(a, outbuf, sizeof(outbuf))) > 0)
            fwrite(outbuf, 1, r, out);

        fclose(out);
    }

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "%s: %s\n", filename, archive_error_string(a));
        exit(1);
    }
    archive_read_free(a);
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

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s tarfile\n", argv[0]);
        exit(1);
    }

    extract_tar(argv[1]);

    return 0;
}