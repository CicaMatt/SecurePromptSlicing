#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libgen.h>

int main() {
    char *archive = "archive.zip";
    char *dest_dir = "/tmp/unpack";
    char unzip_cmd[256];

    struct stat st = {0};

    if (stat(dest_dir, &st) == -1) {
        mkdir(dest_dir, 0755);
    }

    snprintf(unzip_cmd, sizeof(unzip_cmd), "unzip %s -d %s", archive, dest_dir);

    int result = system(unzip_cmd);
    if (result != 0) {
        fprintf(stderr, "Failed to unzip the file.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}