#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *path, const char *dest) {
    struct archive *a;
    struct archive *ext;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_FFLAGS);

    if ((r = archive_read_open_filename(a, path, 10240))) {
        fprintf(stderr, "Error opening %s: %s\n", path, archive_error_string(a));
        return;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char new_name[1024];
        snprintf(new_name, sizeof(new_name), "%s/%s", dest, name);
        archive_entry_set_pathname(entry, new_name);

        r = archive_write_header(ext, entry);
        if (archive_entry_size(entry) > 0) {
            const void *buff;
            size_t size;
            int64_t offset;

            while ((r = archive_read_data_block(a, &buff, &size, &offset)) == ARCHIVE_OK) {
                r = archive_write_data_block(ext, buff, size, offset);
            }
        }
        if (r != ARCHIVE_OK) {
            fprintf(stderr, "Error extracting %s: %s\n", name, archive_error_string(a));
            break;
        }

        r = archive_write_finish_entry(ext);
    }

    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);

    if (r != ARCHIVE_OK) {
        fprintf(stderr, "Error extracting tar file: %s\n", archive_error_string(a));
    }
}

int main() {
    const char *tarfile = "example.tar.gz";
    const char *destination = "/tmp/unpack";

    extract_tar(tarfile, destination);

    return 0;
}