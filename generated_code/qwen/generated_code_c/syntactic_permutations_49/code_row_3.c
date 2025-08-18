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
    archive_read_support_filter_all(a);

    r = archive_read_open_filename(a, "archive.zip", 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "Failed to open archive: %s\n", archive_error_string(a));
        return EXIT_FAILURE;
    }

    while ((r = archive_read_next_header(a, &entry)) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        size_t name_length = strlen(name);
        char outpath[1024];

        snprintf(outpath, sizeof(outpath), "/tmp/unpack/%s", name);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir_p(outpath);
        } else {
            FILE *out;
            char buff[8192];
            size_t bytes_read;

            out = fopen(outpath, "wb");
            if (!out) {
                fprintf(stderr, "Failed to create file: %s\n", outpath);
                continue;
            }

            while ((bytes_read = archive_read_data(a, buff, sizeof(buff))) > 0) {
                fwrite(buff, 1, bytes_read, out);
            }
            fclose(out);
        }

        r = archive_read_data_skip(a);
    }

    if (r != ARCHIVE_EOF) {
        fprintf(stderr, "Failed to read archive: %s\n", archive_error_string(a));
        return EXIT_FAILURE;
    }

    archive_read_free(a);

    return EXIT_SUCCESS;
}

void mkdir_p(const char *path) {
    const char *sep = path;

    while (*sep != '\0') {
        sep = strchr(sep, '/');
        if (sep == NULL) break;
        char part[1024];
        strncpy(part, path, sep - path);
        part[sep - path] = '\0';
        mkdir(part, 0755);
        sep++;
    }

    mkdir(path, 0755);
}