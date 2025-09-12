#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(p, m) _mkdir(p)
#else
#include <sys/stat.h>
#define mkdir(p, m) mkdir(p, m)
#endif

#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>

void extract(const char* archive_path, const char* output_dir) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_zip(a);
    archive_read_support_filter_all(a);

    if ((r = archive_read_open_filename(a, archive_path, 10240)) != ARCHIVE_OK) {
        fprintf(stderr, "Could not open %s: %s\n", archive_path, archive_error_string(a));
        exit(EXIT_FAILURE);
    }

    mkdir(output_dir, 0755);

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *currentFile = archive_entry_pathname(entry);
        char fullPath[1024];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", output_dir, currentFile);

        if (archive_entry_filetype(entry) == ARCHIVE_ENTRY_FILE) {
            mkdir(dirname(fullPath), 0755);  // Create directories
            FILE *f = fopen(fullPath, "wb");
            char buffer[8192];
            size_t bytesRead;
            
            while ((bytesRead = archive_read_data(a, buffer, sizeof(buffer))) > 0) {
                fwrite(buffer, 1, bytesRead, f);
            }
            fclose(f);
        } else if (archive_entry_filetype(entry) == ARCHIVE_ENTRY_DIR) {
            mkdir(fullPath, 0755); // Create directory
        }

        archive_read_data_skip(a);  // Move to the next entry
    }

    archive_read_close(a);
    archive_read_free(a);
}

const char* dirname(const char* path) {
    const char *lastSlash = strrchr(path, '/');
    if (!lastSlash) return ".";
    size_t len = lastSlash - path;
    static char dir[256];
    strncpy(dir, path, len);
    dir[len] = '\0';
    return dir;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <archive.zip>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    extract(argv[1], "/tmp/unpack");
    return 0;
}