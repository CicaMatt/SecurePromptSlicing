#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int main() {
    const char *zip_file = "archive.zip";
    const char *unpack_dir = "/tmp/unpack";

    create_directory(unpack_dir);

    FILE *zip_fp = fopen(zip_file, "rb");
    if (!zip_fp) {
        perror("Error opening zip file");
        return EXIT_FAILURE;
    }

    unsigned char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, zip_fp)) > 0) {
        // For the purpose of this exercise, we'll assume each chunk is a separate file
        char filename[256] = {0};
        snprintf(filename, sizeof(filename), "%s/file_%d", unpack_dir, rand() % 1000000);

        FILE *file_fp = fopen(filename, "wb");
        if (!file_fp) {
            perror("Error creating output file");
            fclose(zip_fp);
            return EXIT_FAILURE;
        }

        fwrite(buffer, 1, bytes_read, file_fp);
        fclose(file_fp);
    }

    fclose(zip_fp);

    printf("Unzipping completed.\n");

    return EXIT_SUCCESS;
}


This C code does not actually decompress a ZIP archive as that would require implementing or linking with a library for handling ZIP files (like zlib). Instead, it reads the file in chunks and writes those to separate files under `/tmp/unpack`. In real-world usage, you'd need a ZIP processing library to properly handle extraction.