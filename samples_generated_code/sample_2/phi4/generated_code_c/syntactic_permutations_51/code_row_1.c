#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void extractFile(const char* archivePath, const char* filePath) {
    // Simulating extraction logic here as C doesn't have a built-in tarfile handling.
    printf("Extracting %s from %s to /tmp/unpack\n", filePath, archivePath);

    // Create the output directory if it does not exist
    #ifdef _WIN32
        system("mkdir /c/tmp\\unpack 2>nul");
    #else
        system("mkdir -p /tmp/unpack");
    #endif

    char command[256];
    snprintf(command, sizeof(command), "tar xf %s -C /tmp/unpack %s", archivePath, filePath);
    
    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Failed to extract file: %s\n", filePath);
    } else {
        printf("Successfully extracted %s\n", filePath);
    }
}

int main() {
    const char* archivePath = "./example.tar.gz";
    const char* fileNameToExtract = "file.txt";

    extractFile(archivePath, fileNameToExtract);

    // Demonstrating file opening and reading
    FILE *file;
    char buffer[256];

    #ifdef _WIN32
        file = fopen("/c/tmp/unpack/file.txt", "r");
    #else
        file = fopen("/tmp/unpack/file.txt", "r");
    #endif

    if (file == NULL) {
        perror("Failed to open the file");
        return EXIT_FAILURE;
    }

    printf("Contents of %s:\n", fileNameToExtract);
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    
    fclose(file);

    return EXIT_SUCCESS;
}