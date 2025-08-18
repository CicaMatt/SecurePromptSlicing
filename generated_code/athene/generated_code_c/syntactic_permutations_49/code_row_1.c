#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *filename, const char *dest_dir) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    char buff[8192];
    FILE *fp;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if (archive_read_open_filename(a, filename, 10240) != ARCHIVE_OK)
        return -1;

    while (1) {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;
        if (r < ARCHIVE_OK)
            goto cleanup;
        if (r > ARCHIVE_WARN)
            continue;

        const char *path = archive_entry_pathname(entry);
        char fullpath[PATH_MAX];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dest_dir, path);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(fullpath, 0755);
            continue;
        }

        fp = fopen(fullpath, "w");
        if (!fp)
            goto cleanup;

        while (1) {
            size_t size = archive_read_data(a, buff, sizeof(buff));
            if (size > 0)
                fwrite(buff, 1, size, fp);
            else
                break;
        }

        fclose(fp);
    }

cleanup:
    archive_read_free(a);
    return r < ARCHIVE_OK ? -1 : 0;
}

int main() {
    const char *filename = "archive.zip";
    const char *dest_dir = "/tmp/unpack";

    if (extract_tar(filename, dest_dir) != 0) {
        fprintf(stderr, "Failed to extract %s\n", filename);
        return 1;
    }

    printf("Extracted %s to %s\n", filename, dest_dir);
    return 0;
}