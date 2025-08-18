#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define SAVE_FOLDER "./pdfs/"

int save_pdf(const char *filename) {
    FILE *inFile = fopen(filename, "rb");
    if (inFile == NULL) return -1;

    char destPath[BUFFER_SIZE];
    snprintf(destPath, sizeof(destPath), "%s%s", SAVE_FOLDER, filename);

    FILE *outFile = fopen(destPath, "wb");
    if (outFile == NULL) {
        fclose(inFile);
        return -2;
    }

    size_t nread;
    char buffer[BUFFER_SIZE];
    while ((nread = fread(buffer, 1, BUFFER_SIZE, inFile)) != 0) {
        fwrite(buffer, 1, nread, outFile);
    }

    fclose(inFile);
    fclose(outFile);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <pdf-file>\n", argv[0]);
        return 1;
    }

    int result = save_pdf(argv[1]);
    if (result == 0) {
        printf("PDF saved successfully.\n");
    } else if (result == -1) {
        perror("Error opening input file");
    } else if (result == -2) {
        perror("Error creating destination file");
    }

    return result;
}