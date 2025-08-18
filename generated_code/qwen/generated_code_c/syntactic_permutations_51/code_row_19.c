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

    r = archive_read_open_filename(a, filename, 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "Failed to open %s: %s\n", filename, archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char outpath[256];
        snprintf(outpath, sizeof(outpath), "/tmp/unpack/%s", name);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir_p(outpath, 0755);
        } else {
            FILE *out = fopen(outpath, "wb");
            if (!out) {
                fprintf(stderr, "Failed to create file %s\n", outpath);
                exit(1);
            }
            const void *buf;
            size_t size;
            la_int64_t offset;

            while (archive_read_data_block(a, &buf, &size, &offset) == ARCHIVE_OK) {
                fwrite(buf, 1, size, out);
            }

            fclose(out);
        }

        archive_read_data_skip(a);
    }

    if ((r = archive_read_free(a)) != ARCHIVE_OK) {
        fprintf(stderr, "Failed to close the tar file: %s\n", archive_error_string(a));
        exit(1);
    }
}

void mkdir_p(const char *path, mode_t mode) {
    const char *sep;
    char pathbuf[256];
    strncpy(pathbuf, path, sizeof(pathbuf));
    sep = strchr(pathbuf, '/');
    while (sep != NULL) {
        if (sep != pathbuf && *(sep-1) == '/') {
            sep++;
            continue;
        }
        *sep = '\0';
        mkdir(pathbuf, mode);
        *sep++ = '/';
    }
    mkdir(pathbuf, mode);
}

int main() {
    extract_tar("example.tar.gz");
    return 0;
}