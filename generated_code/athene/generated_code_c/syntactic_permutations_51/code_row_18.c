#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define TMP_DIR "/tmp/unpack"
#define TAR_FILE "archive.tar.gz"

void extract_tar(const char *path, const char *dest) {
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct archive *a;
    struct archive_entry *entry;

    a = archive_read_new();
    archive_read_support_format_tar(a);
    archive_read_support_filter_gzip(a);
    archive_read_open_fd(a, fd, 10240);

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char fullpath[PATH_MAX];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dest, name);

        if (archive_entry_filetype(entry) == S_IFDIR) {
            mkdir(fullpath, archive_entry_mode(entry));
        } else {
            int out_fd = open(fullpath, O_WRONLY | O_CREAT, archive_entry_mode(entry));
            ssize_t n;
            const void *buff;

            while ((n = archive_read_data(a, &buff, 10240)) > 0) {
                write(out_fd, buff, n);
            }
            close(out_fd);
        }
    }

    archive_read_free(a);
    close(fd);
}

int main() {
    if (mkdir(TMP_DIR, 0755) == -1 && errno != EEXIST) {
        perror("mkdir");
        exit(EXIT_FAILURE);
    }

    extract_tar(TAR_FILE, TMP_DIR);

    return 0;
}