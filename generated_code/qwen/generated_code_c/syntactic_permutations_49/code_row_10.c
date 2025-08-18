#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

#define OUTPUT_DIR "/tmp/unpack"

void extract_file(struct archive *a, struct archive_entry *entry) {
    FILE *fd;
    const char *path = archive_entry_pathname(entry);
    const void *buff;
    size_t size;
    la_int64_t offset;

    fd = fopen(path, "wb+");
    if (!fd) {
        perror("Failed to open file");
        return;
    }

    for (;;) {
        int r = archive_read_data_block(a, &buff, &size, &offset);
        if (r == ARCHIVE_EOF)
            break;
        if (r != ARCHIVE_OK && r != ARCHIVE_WARN) {
            fprintf(stderr, "%s\n", archive_error_string(a));
            fclose(fd);
            return;
        }
        fwrite(buff, 1, size, fd);
    }

    fclose(fd);
}

void create_dir(const char *dir_path) {
    if (mkdir(dir_path, 0755) != 0 && errno != EEXIST) {
        perror("Failed to create directory");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s zipfile\n", argv[0]);
        return EXIT_FAILURE;
    }

    create_dir(OUTPUT_DIR);

    a = archive_read_new();
    archive_read_support_format_zip(a);
    archive_read_support_filter_all(a);

    r = archive_read_open_filename(a, argv[1], 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        return EXIT_FAILURE;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *path = archive_entry_pathname(entry);

        // Create the output path by prepending OUTPUT_DIR
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", OUTPUT_DIR, path);

        // Ensure all directories in the path exist
        for (char *p = full_path + strlen(OUTPUT_DIR) + 1; *p; p++) {
            if (*p == '/') {
                *p = '\0';
                create_dir(full_path);
                *p = '/';
            }
        }

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            create_dir(full_path);
        } else {
            extract_file(a, entry);
        }

        archive_read_data_skip(a);
    }

    r = archive_read_free(a);
    if (r != ARCHIVE_OK)
        fprintf(stderr, "%s\n", archive_error_string(a));

    return EXIT_SUCCESS;
}