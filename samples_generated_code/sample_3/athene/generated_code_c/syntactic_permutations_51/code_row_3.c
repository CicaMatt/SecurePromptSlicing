#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r, fd;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "Error opening %s: %s\n", filename, archive_error_string(a));
        exit(1);
    }

    const char *tmpdir = "/tmp/unpack";
    mkdir(tmpdir, 0755);

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        size_t len = strlen(name);
        char newpath[len + strlen(tmpdir) + 2];
        snprintf(newpath, sizeof(newpath), "%s/%s", tmpdir, name);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(newpath, archive_entry_mode(entry));
        } else {
            fd = open(newpath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                fprintf(stderr, "Error opening %s: %s\n", newpath, strerror(errno));
                exit(1);
            }

            const void *buff;
            size_t size;
            off_t offset;

            while ((r = archive_read_data_block(a, &buff, &size, &offset)) == ARCHIVE_OK) {
                if (write(fd, buff, size) != size) {
                    fprintf(stderr, "Error writing to %s: %s\n", newpath, strerror(errno));
                    exit(1);
                }
            }

            close(fd);
        }
    }

    archive_read_free(a);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return 1;
    }

    extract_tar(argv[1]);

    return 0;
}