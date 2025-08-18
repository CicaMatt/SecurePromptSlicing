#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *path, const char *dest) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    char buffer[8192];
    FILE *fd;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename(a, path, 10240))) {
        fprintf(stderr, "archive_read_open_filename failed: %s\n", archive_error_string(a));
        return r;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char fullpath[1024];
        sprintf(fullpath, "%s/%s", dest, name);

        if (archive_entry_filetype(entry) == S_IFDIR) {
            mkdir(fullpath, 0755);
        } else {
            fd = fopen(fullpath, "w");
            if (!fd) {
                fprintf(stderr, "Could not open file %s for writing: %s\n", fullpath, strerror(errno));
                return -1;
            }
            while (1) {
                size_t size = archive_read_data(a, buffer, sizeof(buffer));
                if (size > 0) {
                    fwrite(buffer, 1, size, fd);
                } else {
                    break;
                }
            }
            fclose(fd);
        }
    }

    r = archive_read_free(a);
    return r;
}

int main() {
    const char *archive_path = "archive.zip";
    const char *dest_dir = "/tmp/unpack";

    if (mkdir(dest_dir, 0755) == -1 && errno != EEXIST) {
        perror("mkdir failed");
        return EXIT_FAILURE;
    }

    int result = extract_tar(archive_path, dest_dir);
    if (result != ARCHIVE_OK) {
        fprintf(stderr, "Extraction failed: %s\n", archive_error_string(a));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}