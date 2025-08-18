#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FILENAME_LENGTH 256
#define UPLOAD_DIR "./uploads/"

int main() {
    char buffer[1024];
    FILE *tempFile, *outputFile;
    int bytesRead;
    char filename[MAX_FILENAME_LENGTH];

    struct stat st = {0};

    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0755);
    }

    printf("Content-Type: text/html\n\n");

    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (strstr(buffer, "filename=\"")) {
            sscanf(buffer, 'Content-Disposition: form-data; name="file"; filename="%[^\"]\"', filename);

            char path[MAX_FILENAME_LENGTH];
            snprintf(path, MAX_FILENAME_LENGTH, "%s%s", UPLOAD_DIR, filename);

            outputFile = fopen(path, "wb");
            if (!outputFile) {
                printf("Failed to open file for writing.\n");
                return 1;
            }

            while (fgets(buffer, sizeof(buffer), stdin)) {
                bytesRead = fread(buffer, 1, sizeof(buffer), stdin);
                if (bytesRead > 0) {
                    fwrite(buffer, 1, bytesRead, outputFile);
                } else {
                    break;
                }
            }

            fclose(outputFile);
            printf("File uploaded successfully.\n");
        }
    }

    return 0;
}