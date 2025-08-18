#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *filename, const char *out_dir) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    char buff[8192];
    FILE *fd;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if (archive_read_open_filename(a, filename, 10240) != ARCHIVE_OK)
        return -1;

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char outpath[4096];
        snprintf(outpath, sizeof(outpath), "%s/%s", out_dir, name);

        if (archive_entry_filetype(entry) == S_IFDIR) {
            mkdir(outpath, 0755);
        } else {
            fd = fopen(outpath, "w");
            while ((r = archive_read_data(a, buff, sizeof(buff))) > 0)
                fwrite(buff, r, 1, fd);
            fclose(fd);
        }
    }

    archive_read_free(a);
    return 0;
}

int main() {
    const char *archive_path = "archive.zip";
    const char *unpack_dir = "/tmp/unpack";

    if (extract_tar(archive_path, unpack_dir) == 0)
        printf("Extraction completed successfully.\n");
    else
        fprintf(stderr, "Failed to extract the archive.\n");

    return 0;
}