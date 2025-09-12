#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <zlib.h>
#include <bzlib.h>

void extract_tar(const char *filename, const char *dest) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    struct archive *a;
    struct archive_entry *entry;
    int flags;

    a = archive_read_new();
    archive_read_support_format_tar(a);
    archive_read_support_compression_gzip(a);
    archive_read_support_compression_bzip2(a);

    if (strstr(filename, ".gz")) {
        archive_read_open(a, file, NULL, NULL, NULL);
    } else if (strstr(filename, ".bz2")) {
        archive_read_open(a, file, NULL, NULL, NULL);
    } else {
        archive_read_open_file(a, filename, 10240);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dest, name);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(path, 0755);
        } else {
            FILE *out = fopen(path, "wb");
            if (!out) {
                perror("Failed to create file");
                archive_read_free(a);
                fclose(file);
                exit(1);
            }

            const void *buff;
            size_t size;
            off_t offset;

            while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
                fwrite(buff, 1, size, out);
            }

            fclose(out);
        }
    }

    archive_read_free(a);
    fclose(file);
}

int main() {
    const char *tarfile = "example.tar.gz";
    const char *dest = "/tmp/unpack";

    extract_tar(tarfile, dest);

    return 0;
}