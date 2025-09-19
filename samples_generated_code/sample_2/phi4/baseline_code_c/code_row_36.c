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

int extract_file(FILE *inzip, FILE *outf, const char *filename, unsigned long filesize) {
    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while (filesize > 0 && (bytes_read = fread(buffer, 1, BUFFER_SIZE, inzip))) {
        fwrite(buffer, 1, bytes_read, outf);
        filesize -= bytes_read;
    }
    return ferror(inzip) || ferror(outf) ? -1 : 0;
}

int main() {
    FILE *inzip = fopen("archive.zip", "rb");
    if (!inzip) {
        perror("Failed to open archive.zip");
        return EXIT_FAILURE;
    }

    create_directory("/tmp/unpack");

    // Skipping the header part of zip file (local file header signature + filename length + extra field length)
    fseek(inzip, 30, SEEK_CUR);

    while (!feof(inzip)) {
        unsigned char local_file_header[26];
        if (fread(local_file_header, 1, sizeof(local_file_header), inzip) != sizeof(local_file_header)) {
            break;
        }

        unsigned short compression_method = *(unsigned short *)&local_file_header[8];
        unsigned long filename_length = *(unsigned short *)&local_file_header[18];
        unsigned short extra_field_length = *(unsigned short *)&local_file_header[20];

        // Skip to the start of the file name
        fseek(inzip, 30 + filename_length + extra_field_length, SEEK_CUR);

        char filename[256];
        if (fread(filename, 1, sizeof(local_file_header) - sizeof(compression_method) - sizeof(filename_length) -
                  sizeof(extra_field_length), inzip) != sizeof(local_file_header) - sizeof(compression_method) -
            sizeof(filename_length) - sizeof(extra_field_length)) {
            break;
        }

        unsigned long compressed_size = *(unsigned long *)&local_file_header[12];
        unsigned long uncompressed_size = *(unsigned long *)&local_file_header[16];

        // Skip the data descriptor
        fseek(inzip, 4, SEEK_CUR);

        char outpath[512];
        snprintf(outpath, sizeof(outpath), "/tmp/unpack/%s", filename);
        FILE *outf = fopen(outpath, "wb");
        if (!outf) {
            perror("Failed to open output file");
            fclose(inzip);
            return EXIT_FAILURE;
        }

        extract_file(inzip, outf, filename, uncompressed_size);

        fclose(outf);
    }

    fclose(inzip);
    return 0;
}
