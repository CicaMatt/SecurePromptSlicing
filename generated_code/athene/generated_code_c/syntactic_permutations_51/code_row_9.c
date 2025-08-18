#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

void unpack_tar(const char *filename, const char *dest) {
    struct archive *a;
    struct archive *ext;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_FFLAGS);

    if (archive_read_open_filename(a, filename, 10240) == ARCHIVE_OK) {
        while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
            const char *name = archive_entry_pathname(entry);
            char newpath[PATH_MAX];
            snprintf(newpath, sizeof(newpath), "%s/%s", dest, name);

            archive_entry_set_pathname(entry, newpath);
            r = archive_write_header(ext, entry);
            if (r != ARCHIVE_OK) {
                fprintf(stderr, "Error extracting %s: %s\n", newpath, archive_error_string(ext));
                continue;
            }
            const void *buff;
            size_t size;
            off_t offset;
            while (1) {
                r = archive_read_data_block(a, &buff, &size, &offset);
                if (r == ARCHIVE_EOF)
                    break;
                if (r != ARCHIVE_OK) {
                    fprintf(stderr, "Error reading %s: %s\n", newpath, archive_error_string(a));
                    break;
                }
                r = archive_write_data_block(ext, buff, size, offset);
                if (r != ARCHIVE_OK) {
                    fprintf(stderr, "Error writing %s: %s\n", newpath, archive_error_string(ext));
                    break;
                }
            }
        }
    } else {
        fprintf(stderr, "Failed to open %s: %s\n", filename, archive_error_string(a));
    }

    archive_read_close(a);
    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return 1;
    }

    const char *dest = "/tmp/unpack";
    unpack_tar(argv[1], dest);

    return 0;
}