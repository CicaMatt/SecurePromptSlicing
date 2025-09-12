#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <archive.h>
#include <archive_entry.h>

void extract_archive(const char *filename, const char *destination) {
    struct archive *a;
    struct archive_entry *entry;
    int flags;
    int r;

    // Ensure the destination directory exists
    mkdir(destination, 0755);

    flags = ARCHIVE_EXTRACT_TIME;
    flags |= ARCHIVE_EXTRACT_PERM;
    flags |= ARCHIVE_EXTRACT_ACL;
    flags |= ARCHIVE_EXTRACT_FFLAGS;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);
    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "%s: %s\n", archive_error_string(a), filename);
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *path = archive_entry_pathname(entry);
        size_t len = strlen(destination) + strlen(path) + 2;
        char full_path[len];
        snprintf(full_path, len, "%s/%s", destination, path);

        if (archive_entry_filetype(entry) == AE_IFDIR)
            mkdir(full_path, archive_entry_perm(entry));
        else {
            int fd = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("open");
                exit(1);
            }
            r = archive_read_data_into_fd(a, fd);
            close(fd);
        }

        if (r != ARCHIVE_OK) {
            fprintf(stderr, "%s\n", archive_error_string(a));
            break;
        }

        r = archive_write_header(a, entry);
        if (r < ARCHIVE_OK)
            fprintf(stderr, "archive_write_header(): %s\n", archive_error_string(a));

        r = archive_read_data_skip(a);
    }

    archive_read_free(a);
}

int main() {
    extract_archive("archive.zip", "/tmp/unpack");
    return 0;
}