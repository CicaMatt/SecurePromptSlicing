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

    if ((r = archive_read_open_filename(a, filename, 10240)) != ARCHIVE_OK) {
        fprintf(stderr, "Error opening %s: %s\n", filename, archive_error_string(a));
        return;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *path = archive_entry_pathname(entry);
        if (path && path[0] != '/') {
            char tmp_path[1024];
            snprintf(tmp_path, sizeof(tmp_path), "/tmp/unpack/%s", path);
            archive_entry_copy_pathname(entry, tmp_path);
        }
        r = archive_write_header(ext, entry);
        if (r == ARCHIVE_OK) {
            const void *buff;
            size_t size;
            off_t offset;

            while ((r = archive_read_data_block(a, &buff, &size, &offset)) == ARCHIVE_OK) {
                if (size > 0)
                    r = archive_write_data_block(ext, buff, size, offset);
            }
        }
    }

    archive_read_free(a);
    archive_write_disk_free(ext);

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "Error extracting %s: %s\n", filename, archive_error_string(a));
    } else {
        printf("Extracted %s successfully.\n", filename);
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return 1;
    }

    extract_tar(argv[1]);

    return 0;
}