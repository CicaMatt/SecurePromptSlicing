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
        fprintf(stderr, "archive_read_open_file() failed: %s\n", archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        const mode_t file_type = archive_entry_filetype(entry);

        if (S_ISDIR(file_type)) {
            mkdir(name, 0755);
        } else if (S_ISREG(file_type)) {
            FILE *out = fopen(name, "wb");
            char buff[16384];
            size_t sz;

            while ((sz = archive_read_data(a, buff, sizeof(buff))) > 0) {
                fwrite(buff, 1, sz, out);
            }
            fclose(out);
        }

        archive_read_data_skip(a);
    }

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "archive_read_next_header() failed: %s\n", archive_error_string(a));
    }

    archive_read_free(a);
}

int main(int argc, char *argv[]) {
    const char *tar_filename = "example.tar.bz2";
    chdir("/tmp/unpack");
    extract_tar(tar_filename);
    return 0;
}