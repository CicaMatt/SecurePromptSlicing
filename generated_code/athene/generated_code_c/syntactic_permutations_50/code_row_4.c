#include <stdio.h>
#include <stdlib.h>
#include <tar.h>

void extract_tar(const char *filename, const char *outdir) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    struct archive *a;
    struct archive_entry *entry;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if (archive_read_open_FILE(a, fp) != ARCHIVE_OK) {
        fprintf(stderr, "Failed to open tar file.\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        int r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;
        if (r != ARCHIVE_OK) {
            fprintf(stderr, "archive_read_next_header: %s\n", archive_error_string(a));
            exit(EXIT_FAILURE);
        }

        const char *name = archive_entry_pathname(entry);
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", outdir, name);

        if (S_ISDIR(archive_entry_mode(entry))) {
            mkdir(path, 0755);
        } else {
            FILE *fout = fopen(path, "w");
            if (!fout) {
                perror("fopen");
                exit(EXIT_FAILURE);
            }

            const void *buff;
            size_t size;
            off_t offset;
            while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
                fwrite(buff, 1, size, fout);
            }
            fclose(fout);
        }
    }

    archive_read_free(a);
    fclose(fp);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    extract_tar(argv[1], "/tmp/unpack");

    return EXIT_SUCCESS;
}