#include <stdio.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *filename, const char *dest) {
    struct archive *a;
    struct archive *ext;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_OWNER | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_TIME);

    if ((r = archive_read_open_filename(a, filename, 10240)) != ARCHIVE_OK) {
        fprintf(stderr, "Error opening %s\n", filename);
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *path = archive_entry_pathname(entry);

        if (mkdir(dest, 0755) == -1 && errno != EEXIST) {
            perror("mkdir");
            exit(1);
        }

        char dest_path[2048];
        snprintf(dest_path, sizeof(dest_path), "%s/%s", dest, path);

        archive_entry_set_pathname(entry, dest_path);
        if ((r = archive_write_header(ext, entry)) != ARCHIVE_OK) {
            fprintf(stderr, "Error extracting %s\n", path);
            exit(1);
        }

        const void *buff;
        size_t size;
        off_t offset;

        while (1) {
            r = archive_read_data_block(a, &buff, &size, &offset);
            if (r == ARCHIVE_EOF)
                break;
            if (r != ARCHIVE_OK) {
                fprintf(stderr, "Error reading %s\n", path);
                exit(1);
            }
            if (archive_write_data_block(ext, buff, size, offset) != ARCHIVE_OK) {
                fprintf(stderr, "Error writing %s\n", dest_path);
                exit(1);
            }
        }
    }

    archive_read_free(a);
    archive_write_free(ext);
}

int main() {
    const char *tarfile = "example.tar.gz";
    const char *destination = "/tmp/unpack";

    extract_tar(tarfile, destination);

    return 0;
}