#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive_read.h>
#include <libarchive/archive_write_disk.h>

int main() {
    struct archive *a, *ext;
    struct archive_entry *entry;
    int flags;
    const void* buff;
    size_t size;
    off_t offset;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_open_filename(a, "archive.zip", 10240);

    ext = archive_write_disk_new();
    flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;
    archive_write_disk_set_options(ext, flags);
    archive_write_disk_set_standard_lookup(ext);

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *filename = archive_entry_pathname(entry);
        if (filename != NULL && filename[0] != '/') { // Ensure it's not an absolute path
            char newpath[1024];
            snprintf(newpath, sizeof(newpath), "/tmp/unpack/%s", filename);
            archive_entry_set_pathname(entry, newpath);
        }
        archive_write_header(ext, entry);
        while (1) {
            offset = archive_filter_bytes(archive_read_next_filter(a), 1);
            int r = archive_read_data_block(a, &buff, &size, &offset);
            if (r == ARCHIVE_EOF)
                break;
            archive_write_data_block(ext, buff, size, offset);
        }
    }

    archive_read_free(a);
    archive_write_disk_free(ext);

    return 0;
}