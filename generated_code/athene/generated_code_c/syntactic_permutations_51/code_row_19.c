#include <stdio.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    const void *buff;
    size_t size;
    off_t offset;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if (archive_read_open_filename(a, filename, 10240)) {
        while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
            const char *name = archive_entry_pathname(entry);
            mode_t mode = archive_entry_mode(entry);

            if (S_ISDIR(mode)) {
                mkdir(name, mode);
            } else {
                FILE *f = fopen(name, "w");
                while ((r = archive_read_data(a, &buff, 10240)) > 0) {
                    fwrite(buff, r, 1, f);
                }
                fclose(f);
            }
        }
    }

    archive_read_free(a);
}

int main() {
    const char *tarfile = "/path/to/archive.tar.gz";
    chdir("/tmp/unpack");
    extract_tar(tarfile);
    return 0;
}