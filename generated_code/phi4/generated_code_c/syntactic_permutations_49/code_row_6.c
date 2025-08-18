#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
    #include <direct.h> 
    #define mkdir(p, m) _mkdir(p)
#else
    #include <sys/stat.h>
#endif

#include "zip.h"

void create_directory(const char *path) {
    struct stat st = {0};
    
    if (stat(path, &st) == -1) {
        if (mkdir(path, 0700) != 0 && errno != EEXIST) {
            fprintf(stderr, "Failed to create directory: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
}

int main() {
    const char *archive_path = "archive.zip";
    const char *extract_dir = "/tmp/unpack";

    create_directory(extract_dir);

    int err;
    zip_t *za = zip_open(archive_path, 0, &err);
    
    if (!za) {
        fprintf(stderr, "Error %d opening archive '%s'\n", err, archive_path);
        return EXIT_FAILURE;
    }

    struct zip_stat st;
    zip_int64_t num_entries = zip_get_num_entries(za, 0);

    for (zip_uint64_t i = 0; i < num_entries; i++) {
        if (zip_stat_index(za, i, 0, &st) == 0) {
            char file_path[1024];
            snprintf(file_path, sizeof(file_path), "%s/%s", extract_dir, st.name);

            if (st.isDirectory) {
                create_directory(file_path);
            } else {
                FILE *file = fopen(file_path, "wb");
                if (!file) {
                    fprintf(stderr, "Failed to open file %s for writing: %s\n", file_path, strerror(errno));
                    zip_close(za);
                    return EXIT_FAILURE;
                }

                zip_file_t *zf = zip_fopen_index(za, i, 0);
                if (zf == NULL) {
                    fclose(file);
                    fprintf(stderr, "Error opening file '%s' in archive\n", st.name);
                    zip_close(za);
                    return EXIT_FAILURE;
                }
                
                char buffer[4096];
                int bytes_read = zip_fread(zf, buffer, sizeof(buffer));
                
                while (bytes_read > 0) {
                    fwrite(buffer, 1, bytes_read, file);
                    bytes_read = zip_fread(zf, buffer, sizeof(buffer));
                }

                fclose(file);
                zip_fclose(zf);
            }
        } else {
            fprintf(stderr, "Error getting info for index %llu\n", i);
        }
    }

    zip_close(za);

    return EXIT_SUCCESS;
}


Note: The above code uses the `libzip` library to handle ZIP files. You will need to link against `libzip` when compiling this program:


gcc -o unzip unzip.c -lzip


Make sure you have `libzip` installed on your system before compiling.