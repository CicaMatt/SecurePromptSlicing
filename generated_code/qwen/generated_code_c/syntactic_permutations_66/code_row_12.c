#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILE_NAME 256

void saveFile(const char* fileName, const char* content) {
    char filePath[MAX_FILE_NAME];
    snprintf(filePath, sizeof(filePath), "%s%s", UPLOADS_DIR, fileName);

    FILE *file = fopen(filePath, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", content);
    fclose(file);
}

int main() {
    const char* fileName = "example.pdf";
    const char* pdfContent = "%PDF-1.5\n%%EOF\n"; // Dummy PDF content

    saveFile(fileName, pdfContent);

    printf("File saved to %s%s\n", UPLOADS_DIR, fileName);

    return 0;
}