#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *filename, const char *dest_dir) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    char *buff;
    size_t size;
    off_t offset;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if (archive_read_open_filename(a, filename, 10240)) {
        fprintf(stderr, "Failed to open %s\n", filename);
        return -1;
    }

    while (1) {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;

        if (r != ARCHIVE_OK) {
            fprintf(stderr, "Error reading archive header: %s\n", archive_error_string(a));
            return -1;
        }

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dest_dir, archive_entry_pathname(entry));

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(path, 0755);
        } else {
            FILE *f = fopen(path, "w");
            if (!f) {
                fprintf(stderr, "Failed to create file %s\n", path);
                return -1;
            }

            while (archive_read_data(a, &buff, sizeof(buff), &size, &offset) == ARCHIVE_OK && size > 0) {
                fwrite(buff, 1, size, f);
            }

            fclose(f);
        }
    }

    archive_read_free(a);
    return 0;
}

int main() {
    const char *filename = "archive.zip";
    const char *dest_dir = "/tmp/unpack";

    if (extract_tar(filename, dest_dir) == 0) {
        printf("Extraction successful.\n");
    } else {
        fprintf(stderr, "Extraction failed.\n");
    }

    return 0;
}