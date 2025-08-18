#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    const void *buff;
    size_t size;
    off_t offset;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);
    if (archive_read_open_filename(a, filename, 10240) != ARCHIVE_OK) {
        fprintf(stderr, "Can't open %s\n", filename);
        exit(1);
    }

    const char *tmpdir = "/tmp/unpack";
    mkdir(tmpdir, 0755);

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", tmpdir, name);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(fullpath, archive_entry_mode(entry));
        } else {
            int fd = open(fullpath, O_WRONLY | O_CREAT | O_TRUNC, archive_entry_mode(entry));
            if (fd < 0) {
                fprintf(stderr, "Can't create %s\n", fullpath);
                exit(1);
            }
            while ((r = archive_read_data_block(a, &buff, &size, &offset)) == ARCHIVE_OK && size > 0) {
                write(fd, buff, size);
            }
            close(fd);
        }
    }

    if (archive_read_free(a) != ARCHIVE_OK) {
        fprintf(stderr, "Error freeing archive\n");
        exit(1);
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return 1;
    }

    extract_tar(argv[1]);

    return 0;
}