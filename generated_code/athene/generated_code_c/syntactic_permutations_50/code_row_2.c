#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *filename, const char *destination) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    char buff[8192];
    FILE *fp;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if (archive_read_open_filename(a, filename, 10240)) {
        while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
            const char *name = archive_entry_pathname(entry);
            char path[PATH_MAX];
            snprintf(path, sizeof(path), "%s/%s", destination, name);

            if (archive_entry_filetype(entry) == S_IFDIR) {
                mkdir(path, 0755);
            } else {
                fp = fopen(path, "w");
                if (!fp) {
                    fprintf(stderr, "Failed to open file %s\n", path);
                    return 1;
                }
                while ((r = archive_read_data(a, buff, sizeof(buff))) > 0) {
                    fwrite(buff, r, 1, fp);
                }
                fclose(fp);
            }
        }
    } else {
        fprintf(stderr, "Failed to open archive: %s\n", archive_error_string(a));
        return 1;
    }

    archive_read_free(a);
    return 0;
}

int main() {
    const char *archive = "archive.zip";
    const char *destination = "/tmp/unpack";

    if (extract_tar(archive, destination) == 0) {
        printf("Extraction successful.\n");
    } else {
        fprintf(stderr, "Extraction failed.\n");
    }

    return 0;
}