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
    int r, fd = open("/tmp/unpack", O_DIRECTORY | O_CREAT, 0755);
    chdir("/tmp/unpack");

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if (archive_read_open_filename(a, filename, 10240)) {
        while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
            const char *name = archive_entry_pathname(entry);
            mode_t mode = archive_entry_mode(entry);
            r = archive_util_unlink(name);

            if (S_ISREG(mode)) {
                int fd2;
                if ((fd2 = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
                    perror(name);
                    continue;
                }
                while ((r = archive_read_data(a, NULL, 10240)) > 0) {
                    write(fd2, a->archive.read_buffer, r);
                }
                close(fd2);
            } else if (S_ISDIR(mode)) {
                mkdir(name, mode & 0777);
            } else {
                archive_entry_clear(entry);
            }
        }
    }

    archive_read_free(a);
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return 1;
    }

    extract_tar(argv[1]);

    return 0;
}