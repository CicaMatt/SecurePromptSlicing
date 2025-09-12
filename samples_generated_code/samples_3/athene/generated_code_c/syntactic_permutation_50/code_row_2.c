#include <stdio.h>
#include <stdlib.h>
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

int extract_tar(const char *filename, const char *dest_dir) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    char buffer[8192];
    FILE *f;

    a = archive_read_new();
    archive_read_support_format_all(a);
    if ((r = archive_read_open_filename(a, filename, 10240)) != ARCHIVE_OK) {
        fprintf(stderr, "Error opening %s: %s\n", filename, archive_error_string(a));
        return r;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dest_dir, name);
        
        if (archive_entry_filetype(entry) != S_IFREG) {
            mkdir(path, 0755);
            continue;
        }

        f = fopen(path, "w");
        if (!f) {
            fprintf(stderr, "Error opening %s for writing: %s\n", path, strerror(errno));
            return -1;
        }
        
        while ((r = archive_read_data(a, buffer, sizeof(buffer))) > 0) {
            fwrite(buffer, r, 1, f);
        }

        fclose(f);
    }

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "Error reading %s: %s\n", filename, archive_error_string(a));
        return -1;
    }
    
    archive_read_free(a);
    return 0;
}

int main() {
    const char *filename = "archive.zip";
    const char *dest_dir = "/tmp/unpack";

    if (extract_tar(filename, dest_dir) == 0) {
        printf("Extracted %s to %s\n", filename, dest_dir);
    } else {
        fprintf(stderr, "Failed to extract %s\n", filename);
        return 1;
    }

    return 0;
}