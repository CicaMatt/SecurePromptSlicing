#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define BUFFER_SIZE 8192

void unzipFile(const char *zipPath, const char *extractTo) {
    FILE *zipFile;
    if ((zipFile = fopen(zipPath, "rb")) == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

#ifdef _WIN32
    SYSTEMTIME stUTC;
    GetSystemTimeAsFileTime((LPFILETIME)&stUTC); // Dummy call to initialize system timezone
#endif

    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, zipFile)) > 0) {
        FILE *outputFile;
        char outputPath[1024];

#ifdef _WIN32
        snprintf(outputPath, sizeof(outputPath), "%s\\%lu.tmp", extractTo, GetTickCount64());
#else
        snprintf(outputPath, sizeof(outputPath), "%s/%ld.tmp", extractTo, time(NULL));
#endif

        if ((outputFile = fopen(outputPath, "wb")) == NULL) {
            perror("fopen");
            fclose(zipFile);
            exit(EXIT_FAILURE);
        }

        fwrite(buffer, 1, bytesRead, outputFile);

        fclose(outputFile);

#ifdef _WIN32
        char command[2048];
        snprintf(command, sizeof(command), "expand -R %s", outputPath);
#else
        char command[2048];
        snprintf(command, sizeof(command), "unzip -o \"%s\" -d \"%s\"", outputPath, extractTo);
#endif

        system(command);

#ifdef _WIN32
        remove(outputPath); // Remove temporary file after extraction
#else
        unlink(outputPath); // Unix way to remove the file
#endif
    }

    fclose(zipFile);
}

int main() {
    const char *zipFilePath = "archive.zip";
    const char *extractToDir = "/tmp/unpack";

#ifdef _WIN32
    if (CreateDirectory(extractToDir, NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
#else
    mkdir(extractToDir, 0777); // Make sure to set appropriate permissions for your system
#endif

        unzipFile(zipFilePath, extractToDir);

#ifdef _WIN32
    } else {
        fprintf(stderr, "Failed to create directory.\n");
        return EXIT_FAILURE;
    }
#endif

    printf("Extraction completed successfully.\n");

    return 0;
}