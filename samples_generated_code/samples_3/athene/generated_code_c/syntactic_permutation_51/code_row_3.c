#include <stdio.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *path) {
    struct archive *a;
    struct archive *ext;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_FFLAGS);

    if ((r = archive_read_open_filename(a, path, 10240)) != ARCHIVE_OK) {
        fprintf(stderr, "Error opening %s: %s\n", path, archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        if (archive_entry_filetype(entry) == S_IFDIR) {
            mkdir(name, 0755);
        } else {
            FILE *f = fopen(name, "w");
            if (!f) {
                fprintf(stderr, "Error creating file %s: %s\n", name, strerror(errno));
                exit(1);
            }
            while ((r = archive_read_data(a, &entry, 10240)) > 0) {
                fwrite(entry, r, 1, f);
            }
            fclose(f);
        }
        if (r != ARCHIVE_EOF && r != ARCHIVE_OK) {
            fprintf(stderr, "Error extracting %s: %s\n", name, archive_error_string(a));
            exit(1);
        }
    }

    archive_read_free(a);
    archive_write_disk_free(ext);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return 1;
    }
    chdir("/tmp/unpack") || (perror("chdir"), exit(1));
    extract_tar(argv[1]);
    return 0;
}