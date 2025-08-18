#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char *file) {
    if (file == NULL || strlen(file) == 0) {
        printf("Error: No file specified.\n");
        return;
    }

    // Construct the file path
    const char *basePath = "./"; // Base directory for images
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s%s", basePath, file);

    // Open the file in read binary mode
    FILE *fp = fopen(filePath, "rb");
    if (fp == NULL) {
        printf("Error: Unable to open file %s.\n", filePath);
        return;
    }

    // Read the contents of the file
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);

    char *content = malloc(fileSize + 1);
    if (content == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(fp);
        return;
    }

    fread(content, 1, fileSize, fp);
    content[fileSize] = '\0';

    // Output the contents
    fwrite(content, 1, fileSize, stdout);

    // Cleanup
    free(content);
    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);
    return EXIT_SUCCESS;
}