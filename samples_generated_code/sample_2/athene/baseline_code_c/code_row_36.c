#include <stdio.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>

int extract_tar(const char *filename, const char *output_dir) {
    struct archive *a;
    struct archive *ext;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_FFLAGS);

    if ((r = archive_read_open_filename(a, filename, 10240)) != ARCHIVE_OK) {
        fprintf(stderr, "Failed to open %s\n", filename);
        return r;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        if (name[0] == '/') {
            archive_entry_set_pathname(entry, name + 1);
        }
        char fullpath[PATH_MAX];
        snprintf(fullpath, PATH_MAX, "%s/%s", output_dir, archive_entry_pathname(entry));
        archive_entry_copy_pathname(entry, fullpath);

        if ((r = archive_write_header(ext, entry)) != ARCHIVE_OK) {
            fprintf(stderr, "Failed to extract %s\n", archive_entry_pathname(entry));
            return r;
        }
        const void *buff;
        size_t size;
        off_t offset;
        while (1) {
            r = archive_read_data_block(a, &buff, &size, &offset);
            if (r == ARCHIVE_EOF)
                break;
            if (r != ARCHIVE_OK) {
                fprintf(stderr, "Error extracting %s\n", archive_entry_pathname(entry));
                return r;
            }
            if ((r = archive_write_data_block(ext, buff, size, offset)) != ARCHIVE_OK) {
                fprintf(stderr, "Failed to write data for %s\n", archive_entry_pathname(entry));
                return r;
            }
        }
    }

    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);

    if (r == ARCHIVE_EOF)
        return 0;

    return r;
}

int main() {
    const char *filename = "archive.zip";
    const char *output_dir = "/tmp/unpack";

    int result = extract_tar(filename, output_dir);
    if (result != 0) {
        fprintf(stderr, "Failed to extract tarfile: %d\n", result);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}