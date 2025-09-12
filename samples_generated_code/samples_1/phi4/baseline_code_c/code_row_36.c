#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

void create_dir(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int main() {
    const char *archive_path = "archive.zip";
    const char *output_dir = "/tmp/unpack";

    // Create output directory if it doesn't exist
    create_dir(output_dir);

    char command[256];
    snprintf(command, sizeof(command), "unzip -o %s -d %s", archive_path, output_dir);
    
    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Failed to unzip the file.\n");
        return EXIT_FAILURE;
    }

    printf("Files extracted successfully to %s\n", output_dir);

    return EXIT_SUCCESS;
}