#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void extract_tar(const char *path, const char *dest) {
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct archive *a;
    struct archive_entry *entry;
    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if (archive_read_open_fd(a, fd, 10240) != ARCHIVE_OK) {
        fprintf(stderr, "Failed to open tar file\n");
        exit(EXIT_FAILURE);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dest, name);

        if (archive_entry_filetype(entry) == S_IFDIR) {
            mkdir(fullpath, archive_entry_mode(entry));
        } else {
            FILE *f = fopen(fullpath, "w");
            if (!f) {
                fprintf(stderr, "Failed to open file %s\n", fullpath);
                continue;
            }
            const void *buff;
            size_t size;
            off_t offset;
            while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
                fwrite(buff, 1, size, f);
            }
            fclose(f);
        }
    }

    archive_read_free(a);
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <tarfile> </tmp/unpack>\n", argv[0]);
        return EXIT_FAILURE;
    }

    extract_tar(argv[1], argv[2]);

    return EXIT_SUCCESS;
}