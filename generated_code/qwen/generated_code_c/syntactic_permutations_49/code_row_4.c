#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

#define DEST_DIR "/tmp/unpack"

void extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    r = archive_read_open_filename(a, filename, 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "archive_read_open_filename() failed: %s\n", archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        const char *dest_name;
        size_t name_len = strlen(name);

        if (name_len == 0 || name[0] == '/') {
            fprintf(stderr, "Invalid filename: %s\n", name);
            exit(1);
        }

        dest_name = malloc(strlen(DEST_DIR) + 1 + name_len + 1);
        if (!dest_name) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        snprintf((char*)dest_name, strlen(DEST_DIR) + 1 + name_len + 1, "%s/%s", DEST_DIR, name);

        const char *p = dest_name;
        for (const char *q = p; *q != '\0'; q++) {
            if (*q == '/') {
                struct stat st;
                char *dir_path = strndup(p, q - p);
                if (stat(dir_path, &st) != 0 && mkdir(dir_path, 0755) != 0) {
                    fprintf(stderr, "mkdir(%s) failed: %s\n", dir_path, strerror(errno));
                    free(dir_path);
                    exit(1);
                }
                free(dir_path);
            }
        }

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            if (mkdir(dest_name, archive_entry_perm(entry)) != 0 && errno != EEXIST) {
                fprintf(stderr, "mkdir(%s) failed: %s\n", dest_name, strerror(errno));
                free((void*)dest_name);
                exit(1);
            }
        } else {
            FILE *f = fopen(dest_name, "wb");
            if (!f) {
                fprintf(stderr, "fopen(%s) failed: %s\n", dest_name, strerror(errno));
                free((void*)dest_name);
                exit(1);
            }

            const void *buf;
            size_t size;
            off_t offset;
            while (archive_read_data_block(a, &buf, &size, &offset) == ARCHIVE_OK) {
                if (fwrite(buf, size, 1, f) != 1) {
                    fprintf(stderr, "fwrite(%s) failed: %s\n", dest_name, strerror(errno));
                    fclose(f);
                    free((void*)dest_name);
                    exit(1);
                }
            }

            fclose(f);
        }

        free((void*)dest_name);

        if (archive_entry_filetype(entry) == AE_IFREG)
            chmod(dest_name, archive_entry_perm(entry));

        r = archive_read_data_skip(a);
        if (r != ARCHIVE_OK) {
            fprintf(stderr, "archive_read_data_skip() failed: %s\n", archive_error_string(a));
            exit(1);
        }
    }

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "archive_read_next_header() failed: %s\n", archive_error_string(a));
        exit(1);
    }

    archive_read_close(a);
    archive_read_free(a);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename.tar.gz\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    extract_tar(filename);

    return 0;
}