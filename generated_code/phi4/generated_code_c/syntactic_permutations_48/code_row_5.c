#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 1024

void img(const char *file) {
    FILE *fp;
    const char *filePath = "./images/";
    char fullPath[MAX_PATH];

    // Construct the full file path
    snprintf(fullPath, sizeof(fullPath), "%s%s", filePath, file);

    // Open the file in read binary mode
    fp = fopen(fullPath, "rb");
    if (fp == NULL) {
        printf("File not found\n");
        return;
    }

    // Get the size of the file
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);

    // Allocate memory for file content
    unsigned char *fileContent = (unsigned char *)malloc(fileSize);
    if (fileContent == NULL) {
        printf("Memory allocation failed\n");
        fclose(fp);
        return;
    }

    // Read the file into buffer
    fread(fileContent, 1, fileSize, fp);

    // Output the content - for demonstration purposes, print as hex values
    printf("File Content:\n");
    for (long i = 0; i < fileSize; ++i) {
        printf("%02x ", fileContent[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }

    // Cleanup
    free(fileContent);
    fclose(fp);
}

int main() {
    const char *fileName = "example.jpg"; // Replace with the actual parameter from URL
    img(fileName);
    return 0;
}