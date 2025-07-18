#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

int main() {
    // Open the archive and extract its contents.
    struct archive *a;
    struct archive_entry *entry;
    int r;
    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_open_filename(a, "archive.zip", 10240);
    for (;;) {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;
        else if (r < ARCHIVE_OK)
            fprintf(stderr, "%s\n", archive_error_string(a));
        else {
            printf("%s ", archive_entry_pathname(entry));
            struct stat *st = archive_entry_stat(entry);
            char *data;
            size_t size;
            archive_read_data_into_buffer(a, &data, &size);
            if (archive_write_disk_set_options(a) != ARCHIVE_OK)
                fprintf(stderr, "%s\n", archive_error_string(a));
            if (archive_write_header(a, entry) != ARCHIVE_OK)
                fprintf(stderr, "%s\n", archive_error_string(a));
            else {
                if (size > 0 && data != NULL) {
                    int fd = open("archive.zip", O_RDWR | O_CREAT);
                    write(fd, data, size);
                    close(fd);
                }
            }
        }
    }
    archive_read_close(a);
    archive_read_free(a);
    return 0;
}