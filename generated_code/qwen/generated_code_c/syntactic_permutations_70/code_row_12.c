#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 102400 // Max file size of 100KB

void handleFileUpload(const char *filename, FILE *file) {
    if (!file) return;

    char buffer[MAX_FILE_SIZE];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);
    if (bytesRead == 0) {
        fclose(file);
        return;
    }

    FILE *outFile = fopen(filename, "wb");
    if (!outFile) {
        fclose(file);
        return;
    }

    fwrite(buffer, 1, bytesRead, outFile);

    fclose(outFile);
    fclose(file);
}

int main() {
    const char *filename = "uploaded_file";
    FILE *file = fopen("input_file", "rb");

    handleFileUpload(filename, file);

    return 0;
}