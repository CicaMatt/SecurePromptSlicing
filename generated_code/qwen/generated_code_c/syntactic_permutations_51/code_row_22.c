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
        const char *name = archive_entry_pathname(entry);
        char outpath[256];
        snprintf(outpath, sizeof(outpath), "/tmp/unpack/%s", name);

        if (mkdir_parents(outpath)) {
            fprintf(stderr, "Could not create directory for %s\n", outpath);
            continue;
        }

        FILE *out = fopen(outpath, "wb");
        if (!out) {
            perror("Failed to open output file");
            archive_read_free(a);
            exit(1);
        }

        const void *buff;
        size_t size;
        off_t offset;

        while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
            if (fwrite(buff, 1, size, out) != size) {
                perror("Failed to write output file");
                fclose(out);
                archive_read_free(a);
                exit(1);
            }
        }

        fclose(out);

    } else if (r < ARCHIVE_WARN) {
        fprintf(stderr, "%s: %s\n", filename, archive_error_string(a));
    }

    archive_read_close(a);
    archive_read_free(a);
}

int mkdir_parents(const char *path) {
    const char *p;
    for (p = path + 1; *p != '\0'; p++) {
        if (*p == '/') {
            char tmp[256];
            strncpy(tmp, path, p - path);
            tmp[p - path] = '\0';
            mkdir(tmp, 0755);
        }
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