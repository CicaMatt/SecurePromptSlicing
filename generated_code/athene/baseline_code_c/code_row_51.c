#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <zlib.h>
#include <bzlib.h>

#define TMP_DIR "/tmp/unpack"
#define BUFFER_SIZE 4096

void extract_tar_gz(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    gzFile gzfile = gzdopen(fileno(file), "rb");
    if (!gzfile) {
        fclose(file);
        perror("gzdopen");
        exit(EXIT_FAILURE);
    }

    char *buffer = malloc(BUFFER_SIZE);
    if (!buffer) {
        gzclose(gzfile);
        fclose(file);
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    struct archive *a;
    struct archive_entry *entry;

    a = archive_read_new();
    archive_read_support_format_tar(a);
    archive_read_support_filter_gzip(a);
    archive_read_open(a, gzfile, NULL, BUFFER_SIZE);

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *pathname = archive_entry_pathname(entry);
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", TMP_DIR, pathname);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(fullpath, 0755);
        } else {
            FILE *out = fopen(fullpath, "wb");
            if (!out) {
                archive_read_close(a);
                archive_read_free(a);
                free(buffer);
                gzclose(gzfile);
                fclose(file);
                perror("fopen");
                exit(EXIT_FAILURE);
            }

            ssize_t bytes_read;
            while ((bytes_read = archive_read_data(a, buffer, BUFFER_SIZE)) > 0) {
                fwrite(buffer, 1, bytes_read, out);
            }

            fclose(out);
        }
    }

    free(buffer);
    archive_read_close(a);
    archive_read_free(a);
    gzclose(gzfile);
    fclose(file);
}

void extract_tar_bz2(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    BZFILE *bzfile;
    int bzerror;
    bzfile = BZ2_bzdopen(fileno(file), "rb", 0, &bzerror);
    if (bzerror != BZ_OK || !bzfile) {
        fclose(file);
        perror("BZ2_bzdopen");
        exit(EXIT_FAILURE);
    }

    char *buffer = malloc(BUFFER_SIZE);
    if (!buffer) {
        BZ2_bzclose(bzfile);
        fclose(file);
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    struct archive *a;
    struct archive_entry *entry;

    a = archive_read_new();
    archive_read_support_format_tar(a);
    archive_read_support_filter_bzip2(a);
    archive_read_open(a, bzfile, NULL, BUFFER_SIZE);

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *pathname = archive_entry_pathname(entry);
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", TMP_DIR, pathname);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(fullpath, 0755);
        } else {
            FILE *out = fopen(fullpath, "wb");
            if (!out) {
                archive_read_close(a);
                archive_read_free(a);
                free(buffer);
                BZ2_bzclose(bzfile);
                fclose(file);
                perror("fopen");
                exit(EXIT_FAILURE);
            }

            ssize_t bytes_read;
            while ((bytes_read = archive_read_data(a, buffer, BUFFER_SIZE)) > 0) {
                fwrite(buffer, 1, bytes_read, out);
            }

            fclose(out);
        }
    }

    free(buffer);
    archive_read_close(a);
    archive_read_free(a);
    BZ2_bzclose(bzfile);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    if (strstr(filename, ".tar.gz")) {
        extract_tar_gz(filename);
    } else if (strstr(filename, ".tar.bz2")) {
        extract_tar_bz2(filename);
    } else {
        fprintf(stderr, "Unsupported file format.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}