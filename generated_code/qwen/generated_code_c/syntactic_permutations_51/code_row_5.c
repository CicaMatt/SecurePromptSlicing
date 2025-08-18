#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <utime.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define TEMP_DIR "/tmp/unpack/"

void extract_tar(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct tar *t = tar_open(fd, TAR_GNUTAR);
    if (!t) {
        perror("tar_open");
        close(fd);
        exit(EXIT_FAILURE);
    }

    struct stat st;
    char buf[4096];
    while (tar_read(t, &st, buf, sizeof(buf)) == 0) {
        char path[1024];
        snprintf(path, sizeof(path), "%s%s", TEMP_DIR, tar_entry_name(&st));

        if (S_ISDIR(st.st_mode)) {
            mkdir(path, st.st_mode);
        } else {
            int out_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, st.st_mode);
            if (out_fd == -1) {
                perror("open");
                tar_close(t);
                close(fd);
                exit(EXIT_FAILURE);
            }
            write(out_fd, buf, st.st_size);
            close(out_fd);

            struct utimbuf times;
            times.actime = times.modtime = st.st_mtime;
            utime(path, &times);
        }

        tar_next(t);
    }

    if (tar_errno(t)) {
        fprintf(stderr, "tar_read error: %s\n", tar_errstr(t));
        tar_close(t);
        close(fd);
        exit(EXIT_FAILURE);
    }

    tar_close(t);
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    mkdir(TEMP_DIR, 0755);

    extract_tar(argv[1]);

    return EXIT_SUCCESS;
}