#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *filename, const char *destination) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_filter_gzip(a);
    archive_read_support_format_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename() failed: %s\n", archive_error_string(a));
        archive_read_free(a);
        return;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char outpath[1024];
        snprintf(outpath, sizeof(outpath), "%s/%s", destination, name);

        FILE *out;
        if ((out = fopen(outpath, "wb")) == NULL) {
            fprintf(stderr, "Could not open output file: %s\n", outpath);
            continue;
        }

        const void *buffer;
        size_t len;
        la_int64_t offset;

        while (archive_read_data_block(a, &buffer, &len, &offset) == ARCHIVE_OK) {
            fwrite(buffer, 1, len, out);
        }
        fclose(out);

        archive_read_data_skip(a);
    }

    if ((r = archive_read_free(a))) {
        fprintf(stderr, "Failed to read the archive: %s\n", archive_error_string(a));
    }
}

int main() {
    const char *tarfile = "example.tar.gz";
    const char *destination = "/tmp/unpack";

    // Ensure the destination directory exists
    if (mkdir(destination, 0755) != 0 && errno != EEXIST) {
        perror("Failed to create destination directory");
        return EXIT_FAILURE;
    }

    extract_tar(tarfile, destination);
    printf("Extraction complete.\n");

    return EXIT_SUCCESS;
}