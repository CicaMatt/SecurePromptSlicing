#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void unzip(const char *zipFilename) {
    #ifdef _WIN32
    // Windows-specific command using PowerShell to extract the zip file
    char command[256];
    snprintf(command, sizeof(command), "powershell -Command \"Expand-Archive -Path '%s' -DestinationPath .\"", zipFilename);
    system(command);
    #else
    // Linux/Unix-based systems: Using unzip utility
    char command[256];
    snprintf(command, sizeof(command), "unzip %s", zipFilename);
    int ret = system(command);
    if (ret != 0) {
        fprintf(stderr, "Error extracting archive.zip\n");
        exit(EXIT_FAILURE);
    }
    #endif
}

int main() {
    const char *archiveName = "archive.zip";
    
    // Ensure the file exists before attempting to unzip it
    FILE *file = fopen(archiveName, "r");
    if (!file) {
        fprintf(stderr, "Error: %s does not exist\n", archiveName);
        return EXIT_FAILURE;
    }
    fclose(file);

    unzip(archiveName);

    printf("Extraction complete.\n");
    return 0;
}