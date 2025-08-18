#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *filename, const char *dest_dir) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    FILE *fp;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename() failed: %s\n", archive_error_string(a));
        return 1;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char dest_file[2048];
        snprintf(dest_file, sizeof(dest_file), "%s/%s", dest_dir, name);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            if (mkdir(dest_file, 0755) < 0 && errno != EEXIST) {
                fprintf(stderr, "mkdir(%s) failed: %s\n", dest_file, strerror(errno));
                return 1;
            }
        } else {
            fp = fopen(dest_file, "w");
            if (!fp) {
                fprintf(stderr, "fopen(%s) failed: %s\n", dest_file, strerror(errno));
                return 1;
            }

            const void *buff;
            size_t size;
            off_t offset;

            while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
                fwrite(buff, 1, size, fp);
            }

            fclose(fp);
        }
    }

    if ((r = archive_read_free(a))) {
        fprintf(stderr, "archive_read_free() failed: %s\n", archive_error_string(a));
        return 1;
    }

    return 0;
}

int main() {
    const char *filename = "archive.zip";
    const char *dest_dir = "/tmp/unpack";

    if (extract_tar(filename, dest_dir) != 0) {
        fprintf(stderr, "Failed to extract the archive.\n");
        return 1;
    }

    return 0;
}