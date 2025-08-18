#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main() {
    const char *tarFilePath = "archive.tar.gz";
    const char *extractPath = "/tmp/unpack";

    // Create the directory if it doesn't exist
    #ifdef _WIN32
        char createDirCmd[256];
        snprintf(createDirCmd, sizeof(createDirCmd), "mkdir %s", extractPath);
        system(createDirCmd);
    #else
        mkdir(extractPath, 0777);
    #endif

    // Open the tar file for reading in binary mode
    FILE *tarFile = fopen(tarFilePath, "rb");
    if (!tarFile) {
        error_exit("Failed to open tar file.");
    }

    char buffer[BUFFER_SIZE];
    int bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, tarFile)) > 0) {
        // Simulate writing to a file (normally you would process the tar archive here)
        FILE *extractedFile = fopen("/tmp/unpack/extracted.txt", "ab");
        if (!extractedFile) {
            fclose(tarFile);
            error_exit("Failed to open extracted file.");
        }

        fwrite(buffer, 1, bytesRead, extractedFile);
        fclose(extractedFile);
    }

    if (ferror(tarFile)) {
        error_exit("Error reading tar file.");
    }

    fclose(tarFile);

    printf("Extraction completed successfully.\n");
    return 0;
}