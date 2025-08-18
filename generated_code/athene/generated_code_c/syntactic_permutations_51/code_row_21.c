#include <stdio.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *filename) {
    struct archive *a;
    struct archive *ext;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);
    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_FFLAGS);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "Error opening %s: %s\n", filename, archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        if (name[0] != '/') { // Ensure we only extract relative paths
            char path[256];
            snprintf(path, sizeof(path), "/tmp/unpack/%s", name);
            archive_entry_set_pathname(entry, path);
            r = archive_write_header(ext, entry);
            if (archive_entry_size_is_set(entry) && archive_entry_size(entry) > 0) {
                const void *buff;
                size_t size;
                off_t offset;
                while ((r = archive_read_data_block(a, &buff, &size, &offset)) == ARCHIVE_OK) {
                    r = archive_write_data_block(ext, buff, size, offset);
                }
            }
        }
    }

    archive_read_free(a);
    archive_write_free(ext);

    if (r != ARCHIVE_EOF && r != ARCHIVE_OK) {
        fprintf(stderr, "Error extracting %s: %s\n", filename, archive_error_string(a));
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return 1;
    }

    extract_tar(argv[1]);

    return 0;
}