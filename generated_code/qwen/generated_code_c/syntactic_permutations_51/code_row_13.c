#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "archive_read_open_filename() failed: %s\n", archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        if (mkdir_p(name)) {
            fprintf(stderr, "Could not create directory for file %s\n", name);
            continue;
        }
        int fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) {
            perror("Failed to open file");
            archive_read_free(a);
            exit(1);
        }

        const void *buffer;
        size_t size;
        la_int64_t offset;
        while (archive_read_data_block(a, &buffer, &size, &offset) == ARCHIVE_OK) {
            write(fd, buffer, size);
        }
        close(fd);
    }

    archive_read_close(a);
    archive_read_free(a);
}

int mkdir_p(const char *path) {
    const char *sep = strrchr(path, '/');
    if (sep && sep != path) {
        char *parent_path = strndup(path, sep - path);
        if (mkdir_p(parent_path)) {
            free(parent_path);
            return 1;
        }
        free(parent_path);
    }

    struct stat st;
    if (stat(path, &st) == 0 && S_ISDIR(st.st_mode)) {
        return 0; // Directory already exists
    }

    int result = mkdir(path, 0755);
    if (result != 0 && errno != EEXIST) {
        perror("mkdir");
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename.tar\n", argv[0]);
        exit(1);
    }

    const char *filename = argv[1];
    extract_tar(filename);

    return 0;
}