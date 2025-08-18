#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *path) {
    struct archive *a;
    struct archive_entry *entry;
    int r, fd;
    const void *buff;
    size_t size;
    off_t offset;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if ((r = archive_read_open_filename(a, path, 10240))) {
        fprintf(stderr, "Error opening %s: %s\n", path, archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        if (strstr(name, "/tmp/unpack") != name) continue; // Ensure we only extract to /tmp/unpack

        mkdirs("/tmp/unpack", 0755); // Create directory structure if needed
        fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, archive_entry_mode(entry));
        if (fd < 0) {
            fprintf(stderr, "Error opening %s: %s\n", name, strerror(errno));
            continue;
        }

        while ((r = archive_read_data_block(a, &buff, &size, &offset)) == ARCHIVE_OK)
            write(fd, buff, size);

        close(fd);
    }
    archive_read_free(a);
}

void mkdirs(const char *dir, mode_t mode) {
    struct stat st;
    if (stat(dir, &st) != 0 && mkdir(dir, mode) != 0) {
        fprintf(stderr, "Error creating directory %s: %s\n", dir, strerror(errno));
        exit(1);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return 1;
    }

    extract_tar(argv[1]);

    return 0;
}