#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>  // For mkdir on Windows
#define PATH_SEPARATOR '\\'
#else
#include <sys/stat.h>
#include <unistd.h>   // For mkdir on Unix-like systems
#define PATH_SEPARATOR '/'
#endif

#include "tar.h"

void extract_tar(const char *filename, const char *dest) {
    struct tar header;
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    mkdir(dest, 0777); // Create destination directory

    while (1) {
        int res = read_header(fp, &header);
        if (res == -1)
            break;   // End of archive
        else if (res < 0) {
            fprintf(stderr, "read_header error\n");
            exit(EXIT_FAILURE);
        }

        char path[256];
        snprintf(path, sizeof(path), "%s%s", dest, header.name);

#ifdef _WIN32
        size_t len = strlen(path);
        if (len > 1 && path[len - 1] == PATH_SEPARATOR)
            path[len - 1] = '\0'; // Remove trailing slash on Windows
#endif

        mkdir_recursively(path);

        if (!is_dir(header)) {
            FILE *out_fp = fopen(path, "wb");
            if (!out_fp) {
                perror("fopen output file");
                exit(EXIT_FAILURE);
            }
            write_data(fp, out_fp, header.size);
            fclose(out_fp);
        }

        skip_data(fp, header);
    }

    fclose(fp);
}

void mkdir_recursively(const char *path) {
    size_t len = strlen(path);
    if (len == 0)
        return;

    for (size_t i = 0; i < len; ++i) {
        if (path[i] == PATH_SEPARATOR) {
            path[i] = '\0';
            mkdir(path, 0777);
            path[i] = PATH_SEPARATOR;
        }
    }

    mkdir(path, 0777);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *archive = argv[1];
    extract_tar(archive, "/tmp/unpack");

    return 0;
}
