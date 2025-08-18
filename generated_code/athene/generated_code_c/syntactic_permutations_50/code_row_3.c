#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *filename, const char *dest_dir) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    char *path;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename() failed: %s\n", archive_error_string(a));
        return r;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        path = archive_entry_pathname(entry);
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dest_dir, path);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(fullpath, 0755);
        } else {
            FILE *f = fopen(fullpath, "w");
            if (!f) {
                fprintf(stderr, "Failed to open file %s for writing: %s\n", fullpath, strerror(errno));
                return -1;
            }
            const void *buff;
            size_t size;
            off_t offset;
            while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
                if (fwrite(buff, 1, size, f) != size) {
                    fprintf(stderr, "Failed to write data to file %s: %s\n", fullpath, strerror(errno));
                    fclose(f);
                    return -1;
                }
            }
            fclose(f);
        }
    }

    r = archive_read_free(a);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "archive_read_free() failed: %s\n", archive_error_string(a));
        return r;
    }

    return 0;
}

int main() {
    const char *filename = "archive.zip";
    const char *dest_dir = "/tmp/unpack";

    if (extract_tar(filename, dest_dir) != 0) {
        fprintf(stderr, "Failed to extract archive\n");
        return 1;
    }

    return 0;
}