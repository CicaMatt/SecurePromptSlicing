#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void extract_tar(const char *filename) {
    const char *command = "tar -xzf %s -C /tmp/unpack";
    char cmd[256];

    snprintf(cmd, sizeof(cmd), command, filename);
    int status = system(cmd);

    if (status != 0) {
        fprintf(stderr, "Error extracting the tar file\n");
        exit(EXIT_FAILURE);
    }
}

void write_to_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", content);
    fclose(file);
}

int main() {
    const char *tar_filename = "/path/to/your/archive.tar.gz";
    
    extract_tar(tar_filename);

    const char *text_content = "Hello, World!\n";
    write_to_file("/tmp/unpack/hello.txt", text_content);

    printf("Extraction and file writing completed.\n");

    return 0;
}