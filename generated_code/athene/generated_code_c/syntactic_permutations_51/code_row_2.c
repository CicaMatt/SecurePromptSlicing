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
        exit(EXIT_FAILURE);
    }

    gzFile gz = gzdopen(fileno(file), "r");
    if (!gz) {
        fclose(file);
        perror("gzdopen");
        exit(EXIT_FAILURE);
    }

    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_gzip(a);
    archive_read_support_format_tar(a);

    if (archive_read_open(a, gz, NULL, NULL) != ARCHIVE_OK) {
        fprintf(stderr, "Failed to open tar.gz: %s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    while ((r = archive_read_next_header(a, &entry)) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", TMP_DIR, name);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(fullpath, 0755);
        } else {
            FILE *out = fopen(fullpath, "wb");
            if (!out) {
                fprintf(stderr, "Failed to open %s for writing\n", fullpath);
                exit(EXIT_FAILURE);
            }
            char buffer[BUFFER_SIZE];
            ssize_t bytes_read;
            while ((bytes_read = archive_read_data(a, buffer, BUFFER_SIZE)) > 0) {
                fwrite(buffer, 1, bytes_read, out);
            }
            fclose(out);
        }
    }

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "Error reading tar.gz: %s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    archive_read_free(a);
    gzclose(gz);
}

void extract_tar_bz2(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    BZFILE *bz = BZ2_bzdopen(file, "r");
    if (!bz) {
        fclose(file);
        perror("BZ2_bzdopen");
        exit(EXIT_FAILURE);
    }

    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_bzip2(a);
    archive_read_support_format_tar(a);

    if (archive_read_open(a, bz, NULL, NULL) != ARCHIVE_OK) {
        fprintf(stderr, "Failed to open tar.bz2: %s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    while ((r = archive_read_next_header(a, &entry)) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", TMP_DIR, name);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(fullpath, 0755);
        } else {
            FILE *out = fopen(fullpath, "wb");
            if (!out) {
                fprintf(stderr, "Failed to open %s for writing\n", fullpath);
                exit(EXIT_FAILURE);
            }
            char buffer[BUFFER_SIZE];
            ssize_t bytes_read;
            while ((bytes_read = archive_read_data(a, buffer, BUFFER_SIZE)) > 0) {
                fwrite(buffer, 1, bytes_read, out);
            }
            fclose(out);
        }
    }

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "Error reading tar.bz2: %s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    archive_read_free(a);
    BZ2_bzclose(bz);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <tar.gz|tar.bz2> <archive>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *format = argv[1];
    const char *path = argv[2];

    if (strcmp(format, "tar.gz") == 0) {
        extract_tar_gz(path);
    } else if (strcmp(format, "tar.bz2") == 0) {
        extract_tar_bz2(path);
    } else {
        fprintf(stderr, "Unsupported format: %s\n", format);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}