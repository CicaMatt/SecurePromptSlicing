#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_files(const char *filename, const char *dest_dir) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    FILE *f;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename failed: %s\n", archive_error_string(a));
        return r;
    }

    while (1) {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;
        if (r != ARCHIVE_OK) {
            fprintf(stderr, "archive_read_next_header failed: %s\n", archive_error_string(a));
            return r;
        }

        const char *path = archive_entry_pathname(entry);
        char dest_path[1024];
        snprintf(dest_path, sizeof(dest_path), "%s/%s", dest_dir, path);

        if (archive_entry_filetype(entry) == S_IFDIR) {
            mkdir(dest_path, 0755);
        } else {
            f = fopen(dest_path, "w");
            if (!f) {
                fprintf(stderr, "Failed to open file %s for writing: %s\n", dest_path, strerror(errno));
                return -1;
            }
            while (1) {
                const void *buff;
                size_t size;
                off_t offset;

                r = archive_read_data_block(a, &buff, &size, &offset);
                if (r == ARCHIVE_EOF)
                    break;
                if (r != ARCHIVE_OK) {
                    fprintf(stderr, "archive_read_data_block failed: %s\n", archive_error_string(a));
                    fclose(f);
                    return r;
                }
                fwrite(buff, 1, size, f);
            }
            fclose(f);
        }
    }

    archive_read_free(a);
    return 0;
}

int main() {
    const char *archive_file = "archive.zip";
    const char *destination_dir = "/tmp/unpack";

    if (mkdir(destination_dir, 0755) == -1 && errno != EEXIST) {
        perror("mkdir");
        return EXIT_FAILURE;
    }

    if (extract_files(archive_file, destination_dir) != 0) {
        fprintf(stderr, "Failed to extract files.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}