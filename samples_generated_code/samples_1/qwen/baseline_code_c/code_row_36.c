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
    archive_read_support_compression_all(a);

    r = archive_read_open_filename(a, "archive.zip", 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        goto cleanup;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        size_t name_len = strlen(name);
        char outpath[256] = "/tmp/unpack/";

        if (name_len > sizeof(outpath) - sizeof("/tmp/unpack/") - 1)
            continue;

        strncat(outpath, name, sizeof(outpath) - sizeof("/tmp/unpack/") - 1);

        switch (archive_entry_filetype(entry)) {
            case AE_IFDIR:
                mkdirp(outpath);
                break;
            case AE_IFREG:
                extract_file(a, entry, outpath);
                break;
            default:
                // Ignore other file types
                break;
        }
    }

    if ((r = archive_read_free(a))) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        return EXIT_FAILURE;
    }

cleanup:
    archive_read_free(a);
    return EXIT_SUCCESS;
}

void mkdirp(const char *path) {
    for (char *p = strchr(path + 1, '/'); p; p = strchr(p + 1, '/')) {
        *p = '\0';
        mkdir(path, 0755);
        *p = '/';
    }
    mkdir(path, 0755);
}

void extract_file(struct archive *a, struct archive_entry *entry, const char *outpath) {
    int fd;
    ssize_t len;
    const void *buff;

    fd = open(outpath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return;
    }

    for (;;) {
        len = archive_read_data_block(a, &buff, NULL, NULL);
        if (len == ARCHIVE_EOF)
            break;
        if (len < 0) {
            fprintf(stderr, "%s\n", archive_error_string(a));
            close(fd);
            unlink(outpath);
            return;
        }
        write(fd, buff, len);
    }

    close(fd);
}