#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_zip(const char *filename, const char *dest_dir) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    char *path;

    a = archive_read_new();
    archive_read_support_format_zip(a);
    archive_read_open_filename(a, filename, 10240);

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        path = archive_entry_pathname(entry);
        size_t len = strlen(dest_dir) + strlen(path) + 2;
        char *fullpath = malloc(len);
        snprintf(fullpath, len, "%s/%s", dest_dir, path);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(fullpath, 0755);
        } else {
            FILE *fp = fopen(fullpath, "w");
            if (!fp) {
                fprintf(stderr, "Failed to open %s\n", fullpath);
                free(fullpath);
                archive_read_free(a);
                return 1;
            }
            while ((r = archive_read_data(a, &fullpath, 10240)) > 0) {
                fwrite(&fullpath, 1, r, fp);
            }
            fclose(fp);
        }

        free(fullpath);
    }

    archive_read_free(a);
    return 0;
}

int main(int argc, char **argv) {
    const char *zip_file = argv[1];
    const char *dest_dir = "/tmp/unpack";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <zipfile>\n", argv[0]);
        return 1;
    }

    if (extract_zip(zip_file, dest_dir) != 0) {
        fprintf(stderr, "Failed to extract files from %s\n", zip_file);
        return 1;
    }

    return 0;
}