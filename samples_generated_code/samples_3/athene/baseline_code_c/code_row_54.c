#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *filename) {
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

    if (archive_read_open_filename(a, filename, 10240)) {
        while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
            const char *pathname = archive_entry_pathname(entry);
            char *tmpPath = malloc(strlen("/tmp/unpack/") + strlen(pathname) + 1);
            if (!tmpPath) exit(EXIT_FAILURE);

            strcpy(tmpPath, "/tmp/unpack/");
            strcat(tmpPath, pathname);
            archive_entry_set_pathname(entry, tmpPath);

            r = archive_write_header(ext, entry);
            if (r == ARCHIVE_OK) {
                while ((r = archive_read_data(a, &buff, &size)) > 0)
                    archive_write_data(ext, buff, size);
            }

            free(tmpPath);
        }
    }

    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    extract_tar(argv[1]);

    return EXIT_SUCCESS;
}