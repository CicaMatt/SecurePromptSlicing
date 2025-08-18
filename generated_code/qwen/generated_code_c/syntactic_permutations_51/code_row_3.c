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
        fprintf(stderr, "%s: %s\n", filename, archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        mode_t filemode = archive_entry_mode(entry);

        if (S_ISDIR(filemode)) {
            mkdir(name, 0755);
        } else if (S_ISREG(filemode)) {
            FILE *out;
            char outpath[256];
            snprintf(outpath, sizeof(outpath), "/tmp/unpack/%s", name);
            char *dir = strdup(outpath);
            *(strrchr(dir, '/')) = '\0';
            mkdir(dir, 0755);
            free(dir);

            out = fopen(outpath, "wb");
            if (!out) {
                perror("Failed to create file");
                continue;
            }

            const void *buffer;
            size_t size;
            la_int64_t offset;

            while (archive_read_data_block(a, &buffer, &size, &offset) == ARCHIVE_OK)
                fwrite(buffer, 1, size, out);

            fclose(out);
        }
    }

    archive_read_free(a);
}

int main() {
    const char *tarfile = "example.tar.gz";
    extract_tar(tarfile);
    return 0;
}