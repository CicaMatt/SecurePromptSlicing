#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *filename, const char *dest_dir) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    char buff[8192];
    size_t len;
    FILE *fd;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open: %s\n", archive_error_string(a));
        return r;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dest_dir, name);

        if (archive_entry_filetype(entry) == S_IFDIR) {
            mkdir(path, 0755);
        } else {
            fd = fopen(path, "w");
            if (!fd) {
                fprintf(stderr, "failed to open %s: %s\n", path, archive_error_string(a));
                return -1;
            }
            while ((len = archive_read_data(a, buff, sizeof(buff))) > 0) {
                fwrite(buff, len, 1, fd);
            }
            fclose(fd);
        }
    }

    r = archive_read_free(a);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "archive_read_free: %s\n", archive_error_string(a));
    }

    return r;
}

int main() {
    const char *filename = "archive.zip";
    const char *dest_dir = "/tmp/unpack";

    extract_tar(filename, dest_dir);

    return 0;
}