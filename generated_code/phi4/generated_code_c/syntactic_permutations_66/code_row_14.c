#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void savePDF(const char *inputFilePath, const char *outputFilePath);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_pdf_path> <output_directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *inputPDFPath = argv[1];
    const char *outputDirectory = argv[2];

    // Construct the output file path by appending ".pdf" to the input filename
    char outputPath[BUFFER_SIZE] = {0};
    snprintf(outputPath, BUFFER_SIZE, "%s/%s.pdf", outputDirectory, strrchr(inputPDFPath, '/') ? strrchr(inputPDFPath, '/') + 1 : inputPDFPath);

    savePDF(inputPDFPath, outputPath);

    return EXIT_SUCCESS;
}

void savePDF(const char *inputFilePath, const char *outputFilePath) {
    FILE *inputFile = fopen(inputFilePath, "rb");
    if (!inputFile) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen(outputFilePath, "wb");
    if (!outputFile) {
        fclose(inputFile);
        perror("Failed to create output file");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, inputFile)) > 0) {
        fwrite(buffer, 1, bytesRead, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
}