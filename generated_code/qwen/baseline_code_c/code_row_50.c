#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>
#include <archive.h>
#include <archive_entry.h>

#define OUTPUT_DIR "/tmp/unpack"

void create_dir_if_not_exists(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0755);
    }
}

int main() {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    create_dir_if_not_exists(OUTPUT_DIR);

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);
    r = archive_read_open_filename(a, "archive.zip", 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        return EXIT_FAILURE;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char output_path[1024];
        snprintf(output_path, sizeof(output_path), "%s/%s", OUTPUT_DIR, name);

        if (S_ISDIR(archive_entry_mode(entry))) {
            create_dir_if_not_exists(output_path);
            continue;
        }

        FILE *out = fopen(output_path, "wb");
        if (!out) {
            fprintf(stderr, "Could not open %s for writing\n", output_path);
            archive_read_free(a);
            return EXIT_FAILURE;
        }

        const void *buf;
        size_t size;
        off_t offset;

        while (archive_read_data_block(a, &buf, &size, &offset) == ARCHIVE_OK) {
            fwrite(buf, 1, size, out);
        }
        fclose(out);

        struct utimbuf times = {archive_entry_mtime(entry), archive_entry_mtime(entry)};
        utime(output_path, &times);
    }

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        return EXIT_FAILURE;
    }

    archive_read_free(a);

    return EXIT_SUCCESS;
}