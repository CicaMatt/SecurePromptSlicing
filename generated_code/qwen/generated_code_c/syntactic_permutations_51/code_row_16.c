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
        fprintf(stderr, "%s: %s\n", "Failed to open the tar file", archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char outpath[256];
        snprintf(outpath, sizeof(outpath), "/tmp/unpack/%s", name);

        if (mkdir_parents(outpath)) {
            fprintf(stderr, "Failed to create directory for %s\n", outpath);
            continue;
        }

        FILE *f = fopen(outpath, "wb+");
        if (!f) {
            perror("Failed to open file for writing");
            continue;
        }

        const void *buffer;
        size_t size;
        la_int64_t offset;

        while (archive_read_data_block(a, &buffer, &size, &offset) == ARCHIVE_OK)
            fwrite(buffer, 1, size, f);

        fclose(f);
    }

    archive_read_free(a);
}

int mkdir_parents(const char *path) {
    char *buf = strdup(path);
    char *p;
    int result = 0;

    if ((p = strchr(buf + 1, '/')) == NULL) {
        free(buf);
        return 0;
    }

    do {
        *p = '\0';
        if (mkdir(buf, 0755) != 0 && errno != EEXIST)
            result = -1;
        *p = '/';
    } while ((p = strchr(p + 1, '/')) != NULL);

    free(buf);
    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    extract_tar(argv[1]);

    return EXIT_SUCCESS;
}