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
    if (archive_read_open_filename(a, path, 10240) != ARCHIVE_OK)
        exit(1);

    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_FFLAGS);

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        printf("Extracting %s\n", archive_entry_pathname(entry));
        if ((r = archive_write_header(ext, entry)) != ARCHIVE_OK)
            exit(1);
        while (1) {
            r = archive_read_data_block(a, &buff, &size, &offset);
            if (r == ARCHIVE_EOF)
                break;
            if (r < ARCHIVE_OK)
                exit(1);
            if (archive_write_data_block(ext, buff, size, offset) != r)
                exit(1);
        }
    }

    archive_read_close(a);
    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);
}

int main() {
    const char *tar_path = "/path/to/your/tarfile.tar.gz";
    chdir("/tmp/unpack");
    extract_tar(tar_path);
    return 0;
}