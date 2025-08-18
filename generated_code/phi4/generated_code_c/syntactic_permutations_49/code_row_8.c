#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>  // For mkdir on Windows
#define PATH_SEPARATOR '\\'
#else
#include <sys/stat.h>
#include <unistd.h>
#define PATH_SEPARATOR '/'
#endif

int main() {
    const char *zipFilePath = "archive.zip";
    const char *targetDirPath = "/tmp/unpack";

#ifdef _WIN32
    if (_mkdir(targetDirPath) != 0 && errno != EEXIST) {
#else
    struct stat st = {0};
    if (stat(targetDirPath, &st) == -1) {
        mkdir(targetDirPath, 0700);
#endif

        fprintf(stderr, "Could not create directory %s\n", targetDirPath);
        return EXIT_FAILURE;
    }

    char command[512];
    snprintf(command, sizeof(command), 
             "unzip -o \"%s\" -d \"%s\"", zipFilePath, targetDirPath);

    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Failed to unzip file\n");
        return EXIT_FAILURE;
    }

    printf("Unzipped successfully to %s\n", targetDirPath);
    return EXIT_SUCCESS;
}