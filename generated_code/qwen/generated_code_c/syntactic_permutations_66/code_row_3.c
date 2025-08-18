#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILENAME_LENGTH 256

int saveFile(const char* filename, const unsigned char* data, size_t dataSize) {
    char filePath[MAX_FILENAME_LENGTH];
    snprintf(filePath, sizeof(filePath), "%s%s", UPLOADS_DIR, filename);

    FILE* file = fopen(filePath, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return -1;
    }

    size_t bytesWritten = fwrite(data, 1, dataSize, file);
    fclose(file);

    if (bytesWritten != dataSize) {
        fprintf(stderr, "Error writing to file\n");
        return -1;
    }

    return 0;
}

int main() {
    // Example PDF data and filename
    unsigned char pdfData[] = { '%', 'P', 'D', 'F', '-', '1', '.', '4', ... }; // Complete PDF binary data here
    const char* pdfFilename = "example.pdf";
    size_t pdfSize = sizeof(pdfData);

    if (saveFile(pdfFilename, pdfData, pdfSize) == 0) {
        printf("File saved successfully.\n");
    } else {
        printf("Failed to save file.\n");
    }

    return 0;
}