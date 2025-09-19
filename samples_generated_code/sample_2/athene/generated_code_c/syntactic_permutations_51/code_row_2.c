#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <zlib.h>
#include <bzlib.h>

#define TMP_DIR "/tmp/unpack"

void *open_tar_file(const char *path, const char *mode) {
    FILE *file = fopen(path, mode);
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    return file;
}

int is_gzipped(void *file) {
    unsigned char buffer[2];
    fread(buffer, 1, 2, (FILE *)file);
    fseek((FILE *)file, 0, SEEK_SET); // Reset file pointer
    return buffer[0] == 0x1f && buffer[1] == 0x8b;
}

int is_bzipped(void *file) {
    unsigned char buffer[3];
    fread(buffer, 1, 3, (FILE *)file);
    fseek((FILE *)file, 0, SEEK_SET); // Reset file pointer
    return buffer[0] == 'B' && buffer[1] == 'Z' && buffer[2] == 'h';
}

void extract_tar(void *file) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if (is_gzipped(file)) {
        archive_read_support_filter_gzip(a);
    } else if (is_bzipped(file)) {
        archive_read_support_filter_bzip2(a);
    }

    r = archive_read_open_FILE(a, file);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "Failed to open archive: %s\n", archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    while (1) {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF) break;
        if (r != ARCHIVE_OK) {
            fprintf(stderr, "Failed to read header: %s\n", archive_error_string(a));
            exit(EXIT_FAILURE);
        }

        const char *path = archive_entry_pathname(entry);
        char full_path[512];
        snprintf(full_path, sizeof(full_path), "%s/%s", TMP_DIR, path);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir(full_path, 0755);
        } else {
            FILE *out = fopen(full_path, "wb");
            if (!out) {
                perror("Failed to create file");
                exit(EXIT_FAILURE);
            }

            const void *buff;
            size_t size;
            off_t offset;
            while (1 == archive_read_data_block(a, &buff, &size, &offset)) {
                fwrite(buff, 1, size, out);
            }
            fclose(out);
        }
    }

    archive_read_free(a);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    void *file = open_tar_file(argv[1], "rb");
    extract_tar(file);
    fclose(file);

    return 0;
}