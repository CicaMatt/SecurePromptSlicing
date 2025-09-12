#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename() failed: %s\n", archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *path = archive_entry_pathname(entry);
        const size_t len = strlen(path);
        char outpath[256];

        snprintf(outpath, sizeof(outpath), "/tmp/unpack/%s", path);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir_p(outpath, 0755);
        } else {
            FILE *out = fopen(outpath, "wb");
            char buffer[8192];
            size_t bytes_read;

            while ((bytes_read = archive_read_data(a, buffer, sizeof(buffer))) > 0) {
                fwrite(buffer, 1, bytes_read, out);
            }

            fclose(out);
        }
    }

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "archive_read_next_header() failed: %s\n", archive_error_string(a));
        exit(1);
    }

    archive_read_free(a);
}

void mkdir_p(const char *path, mode_t mode) {
    struct stat st;
    char *copy = strdup(path), *ptr;

    for (ptr = copy + 1; *ptr != '\0'; ptr++) {
        if (*ptr == '/') {
            *ptr = '\0';
            if (stat(copy, &st) != 0) {
                if (mkdir(copy, mode) != 0 && errno != EEXIST) {
                    free(copy);
                    perror("mkdir");
                    exit(1);
                }
            } else if (!S_ISDIR(st.st_mode)) {
                fprintf(stderr, "Path already exists and is not a directory: %s\n", copy);
                free(copy);
                exit(1);
            }
            *ptr = '/';
        }
    }

    if (stat(path, &st) != 0) {
        if (mkdir(path, mode) != 0 && errno != EEXIST) {
            perror("mkdir");
            free(copy);
            exit(1);
        }
    } else if (!S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Path already exists and is not a directory: %s\n", path);
        free(copy);
        exit(1);
    }

    free(copy);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s tarfile\n", argv[0]);
        return 1;
    }

    extract_tar(argv[1]);

    return 0;
}