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
        fprintf(stderr, "%s\n", archive_error_string(a));
        goto cleanup;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *name = archive_entry_pathname(entry);
        char dest[256];
        snprintf(dest, sizeof(dest), "/tmp/unpack/%s", name);

        if (archive_entry_filetype(entry) == AE_IFDIR) {
            mkdir_p(dest);
        } else {
            FILE *out;
            out = fopen(dest, "wb+");
            if (!out) {
                fprintf(stderr, "Failed to create file %s\n", dest);
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

cleanup:
    archive_read_free(a);
    return 0;
}

void mkdir_p(const char *path) {
    char *pp;
    char *sp;
    char copypath[256];
    struct stat info;

    strcpy(copypath, path);
    pp = copypath;
    while ((sp = strchr(pp, '/')) != 0) {
        if (sp != pp) {
            *sp = '\0';
            if (stat(copypath, &info) != 0) {
                mkdir(copypath, 0755);
            }
            *sp = '/';
        }
        pp = sp + 1;
    }

    if (stat(path, &info) != 0)
        mkdir(path, 0755);
}