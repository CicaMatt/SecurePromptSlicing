#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <unistd.h>

void extract_tar(const char *filename, const char *directory) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if (archive_read_open_FILE(a, file) != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    while (1) {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;
        if (r != ARCHIVE_OK) {
            fprintf(stderr, "%s\n", archive_error_string(a));
            exit(EXIT_FAILURE);
        }
        const char *name = archive_entry_pathname(entry);
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", directory, name);

        if (archive_entry_filetype(entry) == S_IFDIR) {
            mkdir(path, 0755);
        } else {
            FILE *out = fopen(path, "wb");
            if (!out) {
                perror("fopen");
                exit(EXIT_FAILURE);
            }
            const void *buff;
            size_t size;
            off_t offset;
            while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
                fwrite(buff, 1, size, out);
            }
            fclose(out);
        }
    }

    archive_read_free(a);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <tarfile> <directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    const char *directory = argv[2];

    extract_tar(filename, directory);

    return 0;
}