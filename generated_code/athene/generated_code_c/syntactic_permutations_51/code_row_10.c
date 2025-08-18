#include <stdio.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);
    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "Failed to open %s: %s\n", filename, archive_error_string(a));
        exit(1);
    }

    const char *dir = "/tmp/unpack";
    r = mkdir(dir, 0755);
    if (r != 0 && errno != EEXIST) {
        perror("mkdir");
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char path[256];
        snprintf(path, sizeof(path), "%s/%s", dir, name);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(path, archive_entry_mode(entry));
        } else {
            FILE *f = fopen(path, "w");
            if (!f) {
                fprintf(stderr, "Failed to open %s for writing: %s\n", path, strerror(errno));
                exit(1);
            }
            const void *buff;
            size_t size;
            off_t offset;
            while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
                if (fwrite(buff, 1, size, f) != size) {
                    fprintf(stderr, "Failed to write %s: %s\n", path, strerror(errno));
                    exit(1);
                }
            }
            fclose(f);
        }
    }

    archive_read_free(a);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return 1;
    }

    extract_tar(argv[1]);
    return 0;
}