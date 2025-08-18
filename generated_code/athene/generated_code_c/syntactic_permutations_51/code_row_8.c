#include <stdio.h>
#include <stdlib.h>
#include <tar.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

void extract_tar(const char *path, const char *dest) {
    struct archive *a;
    struct archive_entry *entry;
    int r, fd;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if ((r = archive_read_open_filename(a, path, 10240))) {
        fprintf(stderr, "archive_read_open_filename() failed: %s\n", archive_error_string(a));
        exit(1);
    }

    while (1) {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;
        if (r != ARCHIVE_OK) {
            fprintf(stderr, "archive_read_next_header() failed: %s\n", archive_error_string(a));
            exit(1);
        }

        char *fullpath = malloc(strlen(dest) + strlen(archive_entry_pathname(entry)) + 2);
        sprintf(fullpath, "%s/%s", dest, archive_entry_pathname(entry));

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(fullpath, archive_entry_mode(entry));
        } else {
            fd = open(fullpath, O_WRONLY | O_CREAT | O_TRUNC, archive_entry_mode(entry));
            if (fd < 0) {
                fprintf(stderr, "open() failed: %s\n", strerror(errno));
                exit(1);
            }
            const void *buff;
            size_t size;
            off_t offset;

            while ((r = archive_read_data_block(a, &buff, &size, &offset)) == ARCHIVE_OK) {
                if (write(fd, buff, size) < 0) {
                    fprintf(stderr, "write() failed: %s\n", strerror(errno));
                    exit(1);
                }
            }

            close(fd);

            if (r != ARCHIVE_EOF) {
                fprintf(stderr, "archive_read_data_block() failed: %s\n", archive_error_string(a));
                exit(1);
            }
        }

        free(fullpath);
    }

    archive_read_free(a);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <tarfile> <destination>\n", argv[0]);
        return 1;
    }

    const char *tarfile = argv[1];
    const char *dest_dir = argv[2];

    extract_tar(tarfile, dest_dir);

    return 0;
}