#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <zlib.h>
#include <bzlib.h>

#define TMP_DIR "/tmp/unpack"
#define BUFFER_SIZE 1024

void extract_tar_gz(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("fopen");
        exit(1);
    }

    gzFile gzip_file = gzdopen(fileno(file), "rb");
    if (!gzip_file) {
        perror("gzdopen");
        fclose(file);
        exit(1);
    }

    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_tar(a);
    archive_read_support_filter_gzip(a);
    archive_read_open(a, gzip_file, NULL, 1024, NULL);

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        const char *fullpath = malloc(strlen(TMP_DIR) + strlen(name) + 2);
        sprintf(fullpath, "%s/%s", TMP_DIR, name);

        if (archive_entry_filetype(entry) == S_IFDIR) {
            mkdir(fullpath, 0755);
        } else {
            FILE *out = fopen(fullpath, "wb");
            if (!out) {
                perror("fopen");
                free(fullpath);
                exit(1);
            }
            char buffer[BUFFER_SIZE];
            ssize_t n;
            while ((n = archive_read_data(a, buffer, BUFFER_SIZE)) > 0) {
                fwrite(buffer, 1, n, out);
            }
            fclose(out);
        }
        free(fullpath);
    }

    archive_read_free(a);
    gzclose(gzip_file);
}

void extract_tar_bz2(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("fopen");
        exit(1);
    }

    BZFILE *bzip2_file = BZ2_bzdopen(file, "rb");
    if (!bzip2_file) {
        perror("BZ2_bzdopen");
        fclose(file);
        exit(1);
    }

    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_tar(a);
    archive_read_support_filter_bzip2(a);
    archive_read_open(a, bzip2_file, NULL, 1024, NULL);

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        const char *fullpath = malloc(strlen(TMP_DIR) + strlen(name) + 2);
        sprintf(fullpath, "%s/%s", TMP_DIR, name);

        if (archive_entry_filetype(entry) == S_IFDIR) {
            mkdir(fullpath, 0755);
        } else {
            FILE *out = fopen(fullpath, "wb");
            if (!out) {
                perror("fopen");
                free(fullpath);
                exit(1);
            }
            char buffer[BUFFER_SIZE];
            ssize_t n;
            while ((n = archive_read_data(a, buffer, BUFFER_SIZE)) > 0) {
                fwrite(buffer, 1, n, out);
            }
            fclose(out);
        }
        free(fullpath);
    }

    archive_read_free(a);
    BZ2_bzclose(bzip2_file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        exit(1);
    }

    const char *path = argv[1];
    if (strstr(path, ".tar.gz")) {
        extract_tar_gz(path);
    } else if (strstr(path, ".tar.bz2")) {
        extract_tar_bz2(path);
    } else {
        fprintf(stderr, "Unsupported file format\n");
        exit(1);
    }

    return 0;
}