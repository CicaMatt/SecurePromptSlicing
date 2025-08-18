#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define TAR_PATH "example.tar.gz"
#define UNPACK_DIR "/tmp/unpack"

void extract_tar(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open tar file");
        return;
    }

    struct stat st;
    if (stat(UNPACK_DIR, &st) == -1) {
        mkdir(UNPACK_DIR, 0755);
    }

    char buffer[4096];
    struct posix_header *header = (struct posix_header *)buffer;

    while (fread(buffer, sizeof(char), 512, file) == 512) {
        if (header->name[0] == '\0') break;
        
        size_t filesize = strtoul(header->size, NULL, 8);
        char *filepath = malloc(strlen(UNPACK_DIR) + strlen(header->name) + 2);
        sprintf(filepath, "%s/%s", UNPACK_DIR, header->name);

        FILE *out_file = fopen(filepath, "w");
        if (!out_file) {
            perror("Failed to create output file");
            free(filepath);
            continue;
        }

        while (filesize > 0) {
            size_t read_size = fread(buffer, sizeof(char), 512, file);
            fwrite(buffer, sizeof(char), read_size < filesize ? read_size : filesize, out_file);
            filesize -= read_size;
        }

        fclose(out_file);
        free(filepath);

        // Align to next block
        long padding = (filesize + 511) / 512 * 512 - filesize;
        fseek(file, padding, SEEK_CUR);
    }

    fclose(file);
}

int main() {
    extract_tar(TAR_PATH);
    return 0;
}