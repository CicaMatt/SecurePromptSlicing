#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

void extract_tar(const char *filename, const char *outdir) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    char buff[8192];
    FILE *out = NULL;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename: %s\n", archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", outdir, name);

        if (archive_entry_filetype(entry) == S_IFDIR) {
            mkdir(path, 0755);
        } else {
            out = fopen(path, "w");
            if (!out) {
                fprintf(stderr, "Failed to open file %s: %s\n", path, strerror(errno));
                exit(1);
            }
            while ((r = archive_read_data(a, buff, sizeof(buff))) > 0) {
                fwrite(buff, r, 1, out);
            }
            fclose(out);
        }
    }

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "archive_read_next_header: %s\n", archive_error_string(a));
        exit(1);
    }

    archive_read_free(a);
}

int main() {
    extract_tar("archive.zip", "/tmp/unpack");
    return 0;
}