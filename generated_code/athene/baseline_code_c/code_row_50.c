#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *path, const char *dest_dir) {
    struct archive *a;
    struct archive_entry *entry;
    int r, fd;
    const void *buff;
    size_t size;
    off_t offset;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename(a, path, 10240))) {
        fprintf(stderr, "archive_read_open failed: %s\n", archive_error_string(a));
        return r;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char dest_file[1024];
        snprintf(dest_file, sizeof(dest_file), "%s/%s", dest_dir, name);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(dest_file, 0755);
        } else {
            fd = open(dest_file, O_WRONLY | O_CREAT, archive_entry_mode(entry));
            if (fd < 0) {
                fprintf(stderr, "open(%s) failed\n", dest_file);
                return -1;
            }
            while ((r = archive_read_data_block(a, &buff, &size, &offset)) == ARCHIVE_OK) {
                write(fd, buff, size);
            }
            close(fd);
        }
    }

    r = archive_read_free(a);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "archive_read_free failed: %s\n", archive_error_string(a));
        return r;
    }

    return 0;
}

int main() {
    const char *archive_path = "archive.zip";
    const char *dest_dir = "/tmp/unpack";

    if (extract_tar(archive_path, dest_dir) != 0) {
        fprintf(stderr, "Failed to extract archive.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}