#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#if defined(__linux__)
#include <sys/types.h>
#include <dirent.h>
#include <tar.h>
#endif

void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
#ifdef __linux__
    if (argc != 2 || strcmp(argv[1], "--help") == 0) {
        fprintf(stderr, "Usage: %s <archive.zip>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_file = argv[1];
    const char *output_dir = "/tmp/unpack";

    DIR *dir;
    if ((dir = opendir(output_dir)) == NULL) {
        if (mkdir(output_dir, 0777) != 0 && errno != EEXIST) {
            error_exit("Failed to create output directory");
        }
    } else {
        closedir(dir);
    }

    FILE *zip_file = fopen(input_file, "rb");
    if (!zip_file) {
        error_exit("Failed to open input file");
    }

    // Assuming the zip archive is valid tar format for simplicity
    struct stat st;
    if (fstat(fileno(zip_file), &st) != 0) {
        fclose(zip_file);
        error_exit("Failed to get file size");
    }
    off_t file_size = st.st_size;

    char buffer[512];
    while (!feof(zip_file)) {
        int read_bytes = fread(buffer, sizeof(char), sizeof(buffer), zip_file);
        if (ferror(zip_file)) {
            fclose(zip_file);
            error_exit("Error reading archive");
        }

        tar_header_t *header = (tar_header_t *)buffer;
        if (memcmp(header->name, "ustar  \0", 7) != 0 && header->typeflag != '\0') {
            // Move to the next file in the archive
            off_t offset = 512 - read_bytes + ((header->size + 511) & ~511);
            fseek(zip_file, offset, SEEK_CUR);
            continue;
        }

        char filename[256];
        strncpy(filename, header->name, sizeof(filename));
        filename[sizeof(filename) - 1] = '\0';

        // Remove leading slashes from filenames
        while (*filename == '/') {
            filename++;
        }

        char full_path[512];
        snprintf(full_path, sizeof(full_path), "%s/%s", output_dir, filename);

        if (header->typeflag == '5') {  // Directory
            if (mkdir(full_path, 0755) != 0 && errno != EEXIST) {
                fclose(zip_file);
                error_exit("Failed to create directory");
            }
        } else if (header->typeflag == '\0') {  // Regular file
            FILE *out_file = fopen(full_path, "wb");
            if (!out_file) {
                fclose(zip_file);
                error_exit("Failed to open output file");
            }

            off_t size_left = header->size;
            while (size_left > 0) {
                int write_bytes = fwrite(buffer + sizeof(tar_header_t), sizeof(char), 
                        (size_left < sizeof(buffer)) ? size_left : sizeof(buffer), out_file);
                if (ferror(out_file)) {
                    fclose(zip_file);
                    fclose(out_file);
                    error_exit("Error writing file");
                }
                size_left -= write_bytes;
            }

            fclose(out_file);

            // Move to the next file in the archive
            off_t offset = 512 - read_bytes + ((header->size + 511) & ~511);
            fseek(zip_file, offset, SEEK_CUR);
        } else {
            fprintf(stderr, "Skipping unsupported type: %c\n", header->typeflag);
            // Move to the next file in the archive
            off_t offset = 512 - read_bytes + ((header->size + 511) & ~511);
            fseek(zip_file, offset, SEEK_CUR);
        }
    }

    fclose(zip_file);

#else
    fprintf(stderr, "This program is only supported on Linux.\n");
    return EXIT_FAILURE;
#endif

    return EXIT_SUCCESS;
}