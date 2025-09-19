#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

int main() {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    r = archive_read_open_filename(a, "archive.zip", 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);

        char output_path[1024];
        snprintf(output_path, sizeof(output_path), "/tmp/unpack/%s", name);

        FILE *f = fopen(output_path, "wb+");
        if (f != NULL) {
            size_t bytes_read;
            const void *buffer;

            while ((bytes_read = archive_read_data_block(a, &buffer, &bytes_read, NULL)) > 0)
                fwrite(buffer, 1, bytes_read, f);

            fclose(f);
        }

        archive_read_data_skip(a);
    }
    
    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        exit(1);
    }

    archive_read_free(a);
    return 0;
}