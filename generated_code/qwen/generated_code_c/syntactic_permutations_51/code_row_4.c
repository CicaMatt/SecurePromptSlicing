#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename() failed: %s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *pathname = archive_entry_pathname(entry);
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "/tmp/unpack/%s", pathname);

        if (S_ISDIR(archive_entry_mode(entry))) {
            mkdir_p(fullpath, 0755);
        } else {
            FILE *f = fopen(fullpath, "wb+");
            if (!f) {
                fprintf(stderr, "Failed to open file %s for writing: %s\n", fullpath, strerror(errno));
                archive_read_free(a);
                exit(EXIT_FAILURE);
            }

            while ((r = archive_read_data_block(a, &buff, &size, &offset)) == ARCHIVE_OK) {
                fwrite(buff, 1, size, f);
            }
            fclose(f);

            if (r < ARCHIVE_WARN) {
                fprintf(stderr, "archive_read_next_header() failed: %s\n", archive_error_string(a));
                exit(EXIT_FAILURE);
            }

            chmod(fullpath, archive_entry_mode(entry) & 0777);
        }
    }

    archive_read_free(a);
}

void mkdir_p(const char *path, mode_t mode) {
    if (mkdir(path, mode) == -1 && errno != EEXIST) {
        perror("mkdir");
        exit(EXIT_FAILURE);
    }
}

int main() {
    const char *tarfile = "example.tar.gz";
    extract_tar(tarfile);
    return 0;
}