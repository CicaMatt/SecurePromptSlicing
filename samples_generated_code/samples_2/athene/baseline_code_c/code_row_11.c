#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <sys/stat.h>
#include <unistd.h>
#include <archive.h>
#include <archive_entry.h>

int extract_tar(const char *filename, const char *outdir) {
    struct archive *a;
    struct archive_entry *entry;
    int r;
    const void *buff;
    size_t size;
    off_t offset;

    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);

    if (archive_read_open_filename(a, filename, 10240)) {
        fprintf(stderr, "Cannot open %s\n", filename);
        return -1;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        char *name = archive_entry_pathname(entry);

        // Construct the full path
        char fullpath[512];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", outdir, name);

        // Ensure directories exist
        const char *dirname = dirname(fullpath);
        if (mkdir_p(dirname) != 0) {
            return -1;
        }

        // Create the file or directory
        int fd = open(fullpath, O_WRONLY | O_CREAT | O_TRUNC, archive_entry_mode(entry));
        if (fd == -1) {
            perror("open");
            continue;
        }

        while (1) {
            r = archive_read_data_block(a, &buff, &size, &offset);
            if (r == ARCHIVE_EOF)
                break;
            if (r != ARCHIVE_OK) {
                fprintf(stderr, "Error extracting %s\n", name);
                close(fd);
                return -1;
            }
            write(fd, buff, size);
        }

        close(fd);

        // Set the file mode
        chmod(fullpath, archive_entry_mode(entry));
    }

    if (archive_read_free(a) != ARCHIVE_OK) {
        fprintf(stderr, "Failed to free read archive\n");
        return -1;
    }

    return 0;
}

int mkdir_p(const char *dir) {
    struct stat st;

    if (stat(dir, &st) == 0) {
        // Directory exists
        if (S_ISDIR(st.st_mode))
            return 0;
        else
            return -1; // Not a directory
    }

    // Try to create the directory
    if (mkdir(dir, 0755) == 0)
        return 0;

    // Check if it's due to parent directories not existing
    char *parent = strdup(dir);
    const char *last_slash = strrchr(parent, '/');
    if (!last_slash || last_slash == parent) {
        free(parent);
        return -1;
    }

    *last_slash = '\0';
    int res = mkdir_p(parent);
    free(parent);

    if (res != 0)
        return -1;

    // Now try to create the directory again
    if (mkdir(dir, 0755) != 0)
        return -1;

    return 0;
}

int main() {
    const char *filename = "archive.zip";
    const char *outdir = "/tmp/unpack";

    if (extract_tar(filename, outdir) == 0) {
        printf("Extraction completed successfully.\n");
    } else {
        fprintf(stderr, "Failed to extract the archive.\n");
    }

    return 0;
}