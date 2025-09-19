#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <tar.h>

void extract_tar(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    struct stat sb;
    if (stat(filename, &sb) == -1) {
        perror("Failed to get file status");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char *buffer = malloc(sb.st_size);
    if (!buffer) {
        perror("Failed to allocate memory for buffer");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    size_t bytes_read = fread(buffer, 1, sb.st_size, file);
    fclose(file);

    if (bytes_read != sb.st_size) {
        fprintf(stderr, "Error reading file\n");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    char *unpack_dir = "/tmp/unpack";
    mkdir(unpack_dir, 0755);

    struct tar *archive;
    archive = tar_open((const unsigned char *)buffer, TAR_FD, bytes_read);
    if (!archive) {
        fprintf(stderr, "Failed to open tar archive\n");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    struct tar_header *header;
    while ((header = tar_next(archive))) {
        char path[PATH_MAX];
        snprintf(path, sizeof(path), "%s/%s", unpack_dir, header->name);

        if (S_ISDIR(header->mode)) {
            mkdir(path, 0755);
        } else if (S_ISREG(header->mode)) {
            FILE *out = fopen(path, "wb");
            if (!out) {
                perror("Failed to create file");
                tar_close(archive);
                free(buffer);
                exit(EXIT_FAILURE);
            }

            size_t written = fwrite(tar_finddata(archive), 1, header->size_data, out);
            fclose(out);

            if (written != header->size_data) {
                fprintf(stderr, "Error writing file\n");
                tar_close(archive);
                free(buffer);
                exit(EXIT_FAILURE);
            }
        }
    }

    tar_close(archive);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    extract_tar(argv[1]);

    return EXIT_SUCCESS;
}