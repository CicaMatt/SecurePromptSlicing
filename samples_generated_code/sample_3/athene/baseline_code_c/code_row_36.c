#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *filename, const char *dest_dir) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    char buff[8192];
    FILE *fd;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename: %s\n", archive_error_string(a));
        return r;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dest_dir, name);

        if (archive_entry_filetype(entry) == S_IFDIR) {
            mkdir(path, 0755);
            continue;
        }

        fd = fopen(path, "w");
        if (!fd) {
            fprintf(stderr, "fopen: %s\n", path);
            return -1;
        }
        while ((r = archive_read_data(a, buff, sizeof(buff))) > 0) {
            fwrite(buff, r, 1, fd);
        }
        fclose(fd);
    }

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "archive_read_next_header: %s\n", archive_error_string(a));
        return -1;
    }

    archive_read_close(a);
    archive_read_free(a);

    return 0;
}

int main() {
    const char *filename = "archive.zip";
    const char *dest_dir = "/tmp/unpack";

    if (extract_tar(filename, dest_dir) != 0) {
        fprintf(stderr, "Failed to extract %s\n", filename);
        return EXIT_FAILURE;
    }

    printf("Extracted all files from %s to %s\n", filename, dest_dir);

    return EXIT_SUCCESS;
}