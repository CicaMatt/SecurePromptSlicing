#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void img(const char *file) {
    FILE *fp;
    char filePath[256];
    
    // Construct the file path assuming files are stored in a directory named "files"
    snprintf(filePath, sizeof(filePath), "./files/%s", file);
    
    // Open the file in read binary mode
    fp = fopen(filePath, "rb");
    if (fp == NULL) {
        printf("File not found or cannot be opened.\n");
        return;
    }
    
    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    // Read and print the file content
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    img(argv[1]);

    return 0;
}