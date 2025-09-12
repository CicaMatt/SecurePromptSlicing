#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

#define BUFFER_SIZE 8192

void extractFile(FILE *zip, FILE *out) {
    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, zip)) > 0) {
        fwrite(buffer, 1, bytesRead, out);
    }
}

int main() {
    const char *archiveName = "archive.zip";
    FILE *zipFile = fopen(archiveName, "rb");

    if (!zipFile) {
        perror("Error opening archive");
        return EXIT_FAILURE;
    }

    fseek(zipFile, 0, SEEK_END);
    long fileSize = ftell(zipFile);
    rewind(zipFile);

    char buffer[BUFFER_SIZE + 1];
    int fileCount = 0;

    while (fread(buffer, 1, BUFFER_SIZE, zipFile) > 0 || ftell(zipFile) < fileSize) {
        if (strncmp(buffer, "PK\3\4", 4) == 0 || strncmp(buffer, "PK\5\6", 4) == 0) { // Local file header or central directory
            fseek(zipFile, -BUFFER_SIZE + ftell(zipFile), SEEK_SET);

            char fileName[256] = {0};
            int foundFilename = 0;
            while (!foundFilename && fread(buffer, 1, BUFFER_SIZE, zipFile)) {
                for (int i = 0; i < BUFFER_SIZE - 4; ++i) {
                    if (buffer[i] == '\0' && buffer[i + 1] != '\0') {
                        strncpy(fileName, &buffer[i + 1], sizeof(fileName) - 1);
                        fileName[sizeof(fileName) - 1] = '\0';
                        foundFilename = 1;
                        break;
                    }
                }

                if (strncmp(buffer, "PK\3\4", 4) == 0) {
                    fseek(zipFile, 30, SEEK_CUR); // Skip to the size of the compressed data
                    int compressedSize;
                    fread(&compressedSize, 1, 4, zipFile);
                    fseek(zipFile, 16, SEEK_CUR); // Skip to the file header end

                    char filePath[256];
                    snprintf(filePath, sizeof(filePath), "%s/%s", "extracted_files", fileName);

#ifdef _WIN32
                    if (_mkdir("extracted_files") || errno == EEXIST) {}
#else
                    mkdir("extracted_files", 0777);
#endif

                    FILE *outFile = fopen(filePath, "wb");
                    if (!outFile) {
                        perror("Error opening output file");
                        fclose(zipFile);
                        return EXIT_FAILURE;
                    }

                    extractFile(zipFile, outFile);

                    fclose(outFile);
                    fileCount++;
                }
            }
        } else {
            fseek(zipFile, BUFFER_SIZE - 4, SEEK_CUR); // Move ahead
        }
    }

    printf("Extracted %d files.\n", fileCount);
    fclose(zipFile);
    return EXIT_SUCCESS;
}