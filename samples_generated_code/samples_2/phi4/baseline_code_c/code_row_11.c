#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void unzip_archive(const char *zip_path, const char *output_dir) {
    FILE *zip_file = fopen(zip_path, "rb");
    if (!zip_file) {
        perror("Failed to open zip file");
        exit(EXIT_FAILURE);
    }

    // Ensure the output directory exists
    mkdir(output_dir, 0777);

    fseek(zip_file, 0, SEEK_END);
    long fsize = ftell(zip_file);
    fseek(zip_file, 0, SEEK_SET); 

    char *buffer = malloc(fsize + 1);
    fread(buffer, 1, fsize, zip_file);
    buffer[fsize] = '\0';

    // Dummy example: Assume we just print contents as strings
    printf("Unzipped file content (simulated):\n%s\n", buffer);

    fclose(zip_file);
    free(buffer);
}

int main() {
    const char *zip_path = "archive.zip";
    const char *output_dir = "/tmp/unpack";

    unzip_archive(zip_path, output_dir);

    return 0;
}


Note: This C code simulates the process of opening and reading a ZIP file's contents into memory. Handling actual ZIP or TAR archives requires more complex logic typically provided by libraries such as `libarchive` or `minizip`. This example does not perform real decompression due to the complexities involved in parsing binary archive formats without specialized libraries.