#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#define BUFFER_SIZE 1024

void extractZip(const char *zipPath, const char *destination) {
    FILE *zipFile = fopen(zipPath, "rb");
    if (!zipFile) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;
    DIR *dir = opendir(destination);
    
    if (dir == NULL) {
        if (mkdir(destination, 0777) != 0) {
            perror("mkdir");
            fclose(zipFile);
            exit(EXIT_FAILURE);
        }
    } else {
        closedir(dir);
    }

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, zipFile)) > 0) {
        // Simplified extraction logic for demonstration
        char filePath[BUFFER_SIZE];
        snprintf(filePath, sizeof(filePath), "%s/testfile.txt", destination);
        
        FILE *outFile = fopen(filePath, "wb");
        if (!outFile) {
            perror("fopen");
            fclose(zipFile);
            exit(EXIT_FAILURE);
        }

        fwrite(buffer, 1, bytesRead, outFile);

        fclose(outFile);
    }

    fclose(zipFile);
}

int main() {
    const char *zipPath = "archive.zip";
    const char *destination = "/tmp/unpack";

    extractZip(zipPath, destination);

    return 0;
}
