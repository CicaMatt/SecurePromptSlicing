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
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename() failed: %s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *path = archive_entry_pathname(entry);
        const char *outpath = malloc(strlen("/tmp/unpack/") + strlen(path) + 1);
        if (!outpath) {
            fprintf(stderr, "Failed to allocate memory\n");
            exit(EXIT_FAILURE);
        }
        strcpy(outpath, "/tmp/unpack/");
        strcat(outpath, path);

        FILE *fp = fopen(outpath, "wb+");
        if (!fp) {
            fprintf(stderr, "Could not open output file %s\n", outpath);
            free(outpath);
            continue;
        }

        const void *buffer;
        size_t size;
        off_t offset;

        while (archive_read_data_block(a, &buffer, &size, &offset) == ARCHIVE_OK) {
            fwrite(buffer, 1, size, fp);
        }
        fclose(fp);
        free(outpath);
    }

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "Error reading archive: %s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    archive_read_free(a);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    extract_tar(argv[1]);

    return EXIT_SUCCESS;
}