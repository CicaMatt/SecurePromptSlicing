#include <stdio.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>

int extract_tar(const char *filename, const char *outdir) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    char *path;
    FILE *fp;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if (archive_read_open_filename(a, filename, 10240)) {
        while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
            path = archive_entry_pathname(entry);
            char fullpath[1024];
            snprintf(fullpath, sizeof(fullpath), "%s/%s", outdir, path);

            if (archive_entry_filetype(entry) == S_IFDIR) {
                mkdir(fullpath, 0755);
            } else {
                fp = fopen(fullpath, "w");
                if (!fp) {
                    fprintf(stderr, "Failed to create file %s\n", fullpath);
                    return 1;
                }
                while ((r = archive_read_data(a, &path, 1024)) > 0) {
                    fwrite(path, r, 1, fp);
                }
                fclose(fp);
            }
        }
    } else {
        fprintf(stderr, "Failed to open archive: %s\n", filename);
        return 1;
    }

    archive_read_free(a);
    return 0;
}

int main() {
    const char *archive = "archive.zip";
    const char *outdir = "/tmp/unpack";

    if (extract_tar(archive, outdir) != 0) {
        fprintf(stderr, "Failed to extract archive\n");
        return 1;
    }

    return 0;
}