#include <stdio.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *path) {
    struct archive *a;
    struct archive *ext;
    struct archive_entry *entry;
    const void *buff;
    size_t size;
    off_t offset;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);
    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_FFLAGS);

    if (archive_read_open_filename(a, path, 10240) != ARCHIVE_OK)
        exit(1);

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        if (archive_entry_filetype(entry) != AE_IFREG) {
            r = archive_write_header(ext, entry);
            if (r != ARCHIVE_OK)
                fprintf(stderr, "Error writing %s: %s\n", name, archive_error_string(ext));
            continue;
        }
        const char *tmpdir = "/tmp/unpack";
        char newpath[1024];
        snprintf(newpath, sizeof(newpath), "%s/%s", tmpdir, name);
        archive_entry_set_pathname(entry, newpath);

        r = archive_write_header(ext, entry);
        if (r != ARCHIVE_OK) {
            fprintf(stderr, "Error writing %s: %s\n", name, archive_error_string(ext));
            continue;
        }
        while ((r = archive_read_data_block(a, &buff, &size, &offset)) == ARCHIVE_OK && size > 0)
            if (archive_write_data_block(ext, buff, size, offset) != ARCHIVE_OK)
                fprintf(stderr, "Error writing data to %s: %s\n", name, archive_error_string(ext));
        if (r != ARCHIVE_EOF)
            fprintf(stderr, "Error reading %s: %s\n", name, archive_error_string(a));
    }
    archive_read_free(a);
    archive_write_free(ext);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <tarfile>\n", argv[0]);
        exit(1);
    }
    extract_tar(argv[1]);
    return 0;
}