#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h> // For mkdir()
#endif

void createDir(const char *path) {
    #ifdef _WIN32
    _mkdir(path);
    #else
    mkdir(path, 0777);
    #endif
}

int main() {
    FILE *zipFile = fopen("archive.zip", "rb");
    if (!zipFile) {
        perror("Error opening archive.zip");
        return EXIT_FAILURE;
    }

    fseek(zipFile, 0, SEEK_END);
    long fileSize = ftell(zipFile);
    fseek(zipFile, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(zipFile);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, fileSize, zipFile);
    buffer[fileSize] = '\0';
    fclose(zipFile);

    char *fileStart = buffer;
    while ((fileStart = strstr(fileStart, "PK\3\4")) != NULL) {
        if (strncmp(fileStart + 30, "tar", 3) == 0) {
            unsigned int size = *(unsigned int *)(fileStart + 24);
            char *fileNameStart = fileStart + 155;
            while (*fileNameStart != '\000') fileNameStart++;
            fileNameStart++; // Move past the null terminator
            char *fileNameEnd = strstr(fileNameStart, "\000");
            size_t fileNameLength = fileNameEnd - fileNameStart;

            unsigned long offset = *(unsigned int *)(fileStart + 42);
            unsigned long tarFileSize = *(unsigned int *)(fileStart + 46);

            if (strncmp(fileNameStart, "tar", 3) == 0 && tarFileSize > sizeof("PK\003\004")) {
                char *tarData = fileStart + offset;
                FILE *tempTar = fopen("temp.tar", "wb");
                fwrite(tarData, 1, tarFileSize, tempTar);
                fclose(tempTar);

                // Extract tar using a system call to tar command
                char extractCommand[256];
                snprintf(extractCommand, sizeof(extractCommand), "tar -xvf temp.tar");
                int result = system(extractCommand);
                remove("temp.tar");

                if (result != 0) {
                    fprintf(stderr, "Failed to extract .tar file\n");
                    free(buffer);
                    return EXIT_FAILURE;
                }

                break; // Assuming only one nested tar archive
            }
        }
        fileStart++;
    }

    free(buffer);

#ifdef _WIN32
    system("PAUSE");
#endif

    return EXIT_SUCCESS;
}