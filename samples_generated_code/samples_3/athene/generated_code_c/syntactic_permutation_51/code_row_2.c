#include <stdio.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>

void extract_tar(const char *path) {
    struct archive *a;
    struct archive *ext;
    struct archive_entry *entry;
    const void *buff;
    size_t size;
    off_t offset;
    int r;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_FFLAGS);

    if (archive_read_open_filename(a, path, 10240) != ARCHIVE_OK)
        goto cleanup;

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        if (archive_entry_filetype(entry) == S_IFREG) {
            if ((r = archive_write_header(ext, entry)) != ARCHIVE_OK)
                goto cleanup;
            while (1) {
                r = archive_read_data(a, &buff, &size);
                if (r == ARCHIVE_EOF)
                    break;
                if (r < ARCHIVE_OK)
                    goto cleanup;
                if (archive_write_data(ext, buff, size) != r)
                    goto cleanup;
            }
        } else {
            if ((r = archive_write_header(ext, entry)) != ARCHIVE_OK)
                goto cleanup;
        }
    }

cleanup:
    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char tmpdir[] = "/tmp/unpackXXXXXX";
    if (mkdtemp(tmpdir) == NULL) {
        perror("mkdtemp");
        return EXIT_FAILURE;
    }

    chdir(tmpdir);
    extract_tar(argv[1]);

    return 0;
}