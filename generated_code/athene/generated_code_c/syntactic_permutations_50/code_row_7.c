#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *filename, const char *outdir) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    char buff[8192];
    FILE *fp;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "Error opening archive: %s\n", archive_error_string(a));
        return r;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", outdir, name);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(path, 0755);
        } else {
            fp = fopen(path, "w");
            if (!fp) {
                fprintf(stderr, "Error opening file %s: %s\n", path, strerror(errno));
                archive_read_free(a);
                return -1;
            }
            while ((r = archive_read_data(a, buff, sizeof(buff))) > 0) {
                fwrite(buff, r, 1, fp);
            }
            fclose(fp);
        }

        if (r != ARCHIVE_EOF && r != ARCHIVE_OK) {
            fprintf(stderr, "Error reading from archive: %s\n", archive_error_string(a));
            return r;
        }
    }

    archive_read_free(a);
    return ARCHIVE_OK;
}

int main() {
    const char *filename = "archive.zip";
    const char *outdir = "/tmp/unpack";

    if (mkdir(outdir, 0755) == -1 && errno != EEXIST) {
        perror("mkdir");
        return EXIT_FAILURE;
    }

    int result = extract_tar(filename, outdir);
    if (result != ARCHIVE_OK) {
        fprintf(stderr, "Failed to extract archive: %s\n", archive_error_string(archive_read_new()));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}