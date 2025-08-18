#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *path) {
    struct archive *a;
    struct archive_entry *entry;
    int r, fd;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename(a, path, 10240)) != ARCHIVE_OK)
        return 1;

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *filename = archive_entry_pathname(entry);
        mode_t file_perm = archive_entry_perm(entry);

        if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, file_perm)) < 0) {
            perror(filename);
            return 1;
        }
        while (1) {
            size_t size;
            const void *buff;
            r = archive_read_data_block(a, &buff, &size, NULL);
            if (r == ARCHIVE_EOF)
                break;
            if (r != ARCHIVE_OK || write(fd, buff, size) < 0) {
                perror(filename);
                return 1;
            }
        }
        close(fd);
    }

    archive_read_free(a);
    return 0;
}

int main() {
    const char *archive_path = "archive.zip";
    if (extract_tar(archive_path) == 0)
        printf("Extraction successful\n");
    else
        fprintf(stderr, "Failed to extract the archive.\n");

    return 0;
}