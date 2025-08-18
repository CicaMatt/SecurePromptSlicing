#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *filename, const char *dest_dir) {
    struct archive *a;
    struct archive_entry *entry;
    int r, fd;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "Error opening %s: %s\n", filename, archive_error_string(a));
        return -1;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char path[256];
        snprintf(path, sizeof(path), "%s/%s", dest_dir, name);

        if ((fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0755)) < 0) {
            fprintf(stderr, "Error opening %s: %s\n", path, archive_error_string(a));
            continue;
        }

        while ((r = archive_read_data_into_fd(a, fd))) {
            if (r != ARCHIVE_OK) {
                close(fd);
                break;
            }
        }
        close(fd);
    }

    r = archive_read_free(a);
    return r == ARCHIVE_OK ? 0 : -1;
}

int main() {
    const char *zip_file = "archive.zip";
    const char *dest_dir = "/tmp/unpack";

    if (extract_tar(zip_file, dest_dir) < 0) {
        fprintf(stderr, "Failed to extract %s to %s\n", zip_file, dest_dir);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}