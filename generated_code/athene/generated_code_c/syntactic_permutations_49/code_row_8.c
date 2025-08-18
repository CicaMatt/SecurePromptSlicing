#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *filename, const char *outdir) {
    struct archive *a;
    struct archive_entry *entry;
    int r, fd;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "Failed to open %s: %s\n", filename, archive_error_string(a));
        return -1;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char path[2048];
        snprintf(path, sizeof(path), "%s/%s", outdir, name);

        if ((r = archive_entry_filetype(entry)) == AE_IFDIR) {
            mkdir(path, 0755);
        } else {
            fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                fprintf(stderr, "Failed to create file %s\n", path);
                return -1;
            }
            while ((r = archive_read_data_into_fd(a, fd)) > 0);
            close(fd);
        }

        if (r != ARCHIVE_OK) {
            fprintf(stderr, "Error extracting %s: %s\n", name, archive_error_string(a));
            return -1;
        }
    }

    r = archive_read_free(a);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "Failed to free archive resources: %s\n", archive_error_string(a));
        return -1;
    }

    return 0;
}

int main() {
    const char *filename = "archive.zip";
    const char *outdir = "/tmp/unpack";

    if (extract_tar(filename, outdir) == 0) {
        printf("Extraction completed successfully.\n");
    } else {
        fprintf(stderr, "Extraction failed.\n");
    }

    return 0;
}