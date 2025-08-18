#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createUploadsDirectory() {
    const char *path = "./uploads";
    struct stat st = {0};

    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pdf_file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *inputFilePath = argv[1];
    createUploadsDirectory();

    char outputFilePath[256];
    snprintf(outputFilePath, sizeof(outputFilePath), "./uploads/%s", strrchr(inputFilePath, '/') ? strrchr(inputFilePath, '/') + 1 : inputFilePath);

    FILE *sourceFile = fopen(inputFilePath, "rb");
    if (!sourceFile) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    FILE *destFile = fopen(outputFilePath, "wb");
    if (!destFile) {
        fclose(sourceFile);
        perror("Failed to open output file");
        return EXIT_FAILURE;
    }

    const size_t bufferSize = 4096;
    char buffer[bufferSize];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, bufferSize, sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destFile);
    }

    fclose(sourceFile);
    fclose(destFile);

    printf("PDF file copied successfully to %s\n", outputFilePath);
    return EXIT_SUCCESS;
}


To compile and run this program:

1. Save the code to a file, for example `copy_pdf.c`.
2. Compile it using: `gcc copy_pdf.c -o copy_pdf`
3. Run it with: `./copy_pdf <path_to_your_pdf>`