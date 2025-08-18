#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

int extract_tar(const char *filename) {
    struct archive *a;
    struct archive_entry *entry;
    int flags;
    int r;

    /* Select which attributes we want to restore. */
    flags = ARCHIVE_EXTRACT_TIME;
    flags |= ARCHIVE_EXTRACT_PERM;
    flags |= ARCHIVE_EXTRACT_ACL;
    flags |= ARCHIVE_EXTRACT_FFLAGS;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);
    r = archive_read_open_filename(a, filename, 10240);

    if (r != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        return 1;
    }

    for (;;) {
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break;
        if (r < ARCHIVE_OK)
            fprintf(stderr, "%s\n", archive_error_string(a));
        if (r < ARCHIVE_WARN) {
            archive_read_free(a);
            return 1;
        }

        char *outpath = malloc(strlen("/tmp/unpack/") + strlen(archive_entry_pathname(entry)) + 1);
        strcpy(outpath, "/tmp/unpack/");
        strcat(outpath, archive_entry_pathname(entry));

        r = archive_read_extract(a, entry, flags);
        if (r < ARCHIVE_OK)
            fprintf(stderr, "%s\n", archive_error_string(a));
        if (r < ARCHIVE_WARN) {
            free(outpath);
            archive_read_free(a);
            return 1;
        }

        free(outpath);
    }

    archive_read_close(a);
    archive_read_free(a);

    return 0;
}

int main() {
    const char *tarfile = "example.tar.gz"; // Replace with your tar file
    if (extract_tar(tarfile) != 0) {
        fprintf(stderr, "Failed to extract %s\n", tarfile);
        return EXIT_FAILURE;
    }
    printf("Extraction successful.\n");
    return EXIT_SUCCESS;
}