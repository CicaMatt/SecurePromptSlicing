#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <tar.h>
#include <zlib.h>
#include <bzlib.h>

#define TMP_DIR "/tmp/unpack"
#define BUFFER_SIZE 1024

void extract_tar_gz(const char *path) {
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int ret;
    struct archive *a;
    struct archive_entry *entry;
    const void *buff;
    size_t size;
    off_t offset;

    a = archive_read_new();
    archive_read_support_format_tar(a);
    archive_read_support_filter_gzip(a);
    archive_read_open_fd(a, fd, BUFFER_SIZE);

    while (1) {
        ret = archive_read_next_header(a, &entry);
        if (ret == ARCHIVE_EOF)
            break;
        if (ret != ARCHIVE_OK) {
            fprintf(stderr, "archive_read_next_header: %s\n", archive_error_string(a));
            exit(EXIT_FAILURE);
        }

        const char *name = archive_entry_pathname(entry);
        mode_t mode = archive_entry_mode(entry);

        char dest[PATH_MAX];
        snprintf(dest, sizeof(dest), "%s/%s", TMP_DIR, name);

        if (S_ISDIR(mode)) {
            mkdir(dest, mode);
        } else {
            int out_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            while (1) {
                size = archive_read_data(a, &buff, BUFFER_SIZE);
                if (size > 0) {
                    write(out_fd, buff, size);
                } else {
                    break;
                }
            }
            close(out_fd);
        }
    }

    archive_read_free(a);
    close(fd);
}

void extract_tar_bz2(const char *path) {
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int ret;
    struct archive *a;
    struct archive_entry *entry;
    const void *buff;
    size_t size;
    off_t offset;

    a = archive_read_new();
    archive_read_support_format_tar(a);
    archive_read_support_filter_bzip2(a);
    archive_read_open_fd(a, fd, BUFFER_SIZE);

    while (1) {
        ret = archive_read_next_header(a, &entry);
        if (ret == ARCHIVE_EOF)
            break;
        if (ret != ARCHIVE_OK) {
            fprintf(stderr, "archive_read_next_header: %s\n", archive_error_string(a));
            exit(EXIT_FAILURE);
        }

        const char *name = archive_entry_pathname(entry);
        mode_t mode = archive_entry_mode(entry);

        char dest[PATH_MAX];
        snprintf(dest, sizeof(dest), "%s/%s", TMP_DIR, name);

        if (S_ISDIR(mode)) {
            mkdir(dest, mode);
        } else {
            int out_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            while (1) {
                size = archive_read_data(a, &buff, BUFFER_SIZE);
                if (size > 0) {
                    write(out_fd, buff, size);
                } else {
                    break;
                }
            }
            close(out_fd);
        }
    }

    archive_read_free(a);
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *path = argv[1];
    char *ext = strrchr(path, '.');

    mkdir(TMP_DIR, 0755);

    if (strcmp(ext, ".tar.gz") == 0) {
        extract_tar_gz(path);
    } else if (strcmp(ext, ".tar.bz2") == 0) {
        extract_tar_bz2(path);
    } else {
        fprintf(stderr, "Unsupported file format\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}