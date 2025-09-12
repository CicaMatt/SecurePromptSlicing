#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *filename, const char *dest_dir) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    char buf[8192];
    FILE *fp;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "Error opening file: %s\n", archive_error_string(a));
        return r;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dest_dir, name);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(path, 0755);
        } else {
            fp = fopen(path, "w");
            if (!fp) {
                fprintf(stderr, "Error opening file %s: %s\n", path, strerror(errno));
                return -1;
            }
            while ((r = archive_read_data(a, buf, sizeof(buf))) > 0) {
                fwrite(buf, r, 1, fp);
            }
            fclose(fp);
        }
    }

    if (archive_read_free(a)) {
        fprintf(stderr, "Error freeing archive: %s\n", archive_error_string(a));
        return -1;
    }

    return 0;
}

int main() {
    const char *filename = "archive.zip";
    const char *dest_dir = "/tmp/unpack";

    if (extract_tar(filename, dest_dir) == 0) {
        printf("Extraction completed successfully.\n");
    } else {
        fprintf(stderr, "Extraction failed.\n");
    }

    return 0;
}