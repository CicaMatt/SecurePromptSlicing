#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *filename, const char *destination) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    const void *buff;
    size_t size;
    off_t offset;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "Error opening %s: %s\n", filename, archive_error_string(a));
        return r;
    }

    for (;;) {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;
        if (r != ARCHIVE_OK) {
            fprintf(stderr, "Error reading header: %s\n", archive_error_string(a));
            archive_read_free(a);
            return r;
        }
        const char *name = archive_entry_pathname(entry);

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", destination, name);
        FILE *f = fopen(path, "w");
        if (!f) {
            fprintf(stderr, "Error opening %s for writing: %s\n", path, strerror(errno));
            archive_read_free(a);
            return -1;
        }

        while (1) {
            r = archive_read_data_block(a, &buff, &size, &offset);
            if (r == ARCHIVE_EOF)
                break;
            if (r != ARCHIVE_OK || fwrite(buff, 1, size, f) != size) {
                fprintf(stderr, "Error writing to %s: %s\n", path, archive_error_string(a));
                fclose(f);
                archive_read_free(a);
                return -1;
            }
        }

        fclose(f);
    }

    archive_read_free(a);
    return 0;
}

int main() {
    const char *archive = "archive.zip";
    const char *destination = "/tmp/unpack";

    if (extract_tar(archive, destination) != 0) {
        fprintf(stderr, "Failed to extract the archive.\n");
        return EXIT_FAILURE;
    }

    printf("Archive extracted successfully.\n");
    return EXIT_SUCCESS;
}