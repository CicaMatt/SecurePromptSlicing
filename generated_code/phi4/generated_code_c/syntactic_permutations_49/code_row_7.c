#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

// Function declarations
int createDirectory(const char *path);
void unzipArchive(const char *archivePath, const char *outputDir);

int main() {
    const char *archiveName = "archive.zip";
    const char *extractToDir = "/tmp/unpack";

    // Ensure the target directory exists
    if (createDirectory(extractToDir) != 0) {
        fprintf(stderr, "Failed to create directory %s\n", extractToDir);
        return EXIT_FAILURE;
    }

    // Unzip the archive
    unzipArchive(archiveName, extractToDir);

    return EXIT_SUCCESS;
}

int createDirectory(const char *path) {
    struct stat st = {0};

    if (stat(path, &st) == -1) {
        int ret = mkdir(path, 0700);
        if (ret != 0 && errno != EEXIST) {
            perror("mkdir");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

void unzipArchive(const char *archivePath, const char *outputDir) {
    // Construct the command to extract the zip file
    char command[512];
    snprintf(command, sizeof(command), "unzip -o %s -d %s", archivePath, outputDir);

    // Execute the unzip command
    int ret = system(command);
    if (ret != 0) {
        fprintf(stderr, "Failed to unzip %s\n", archivePath);
        exit(EXIT_FAILURE);
    }
}