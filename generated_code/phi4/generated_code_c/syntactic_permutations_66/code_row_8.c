#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create "uploads" directory if not exists
void ensure_uploads_directory() {
    char command[256];
    snprintf(command, sizeof(command), "mkdir -p uploads");
    system(command);
}

int main(int argc, char *argv[]) {
    // Check if a file path is provided as an argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path_to_pdf_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *inputFilePath = argv[1];
    const char *outputDirectory = "./uploads/";
    char outputPath[512];

    // Check if the input file exists
    FILE *file = fopen(inputFilePath, "rb");
    if (!file) {
        perror("Failed to open the input PDF file");
        return EXIT_FAILURE;
    }
    fclose(file);

    // Ensure the uploads directory exists
    ensure_uploads_directory();

    // Construct output path
    snprintf(outputPath, sizeof(outputPath), "%s%s", outputDirectory, strrchr(inputFilePath, '/') ? strrchr(inputFilePath, '/') + 1 : inputFilePath);

    // Copy file to the uploads directory
    FILE *input = fopen(inputFilePath, "rb");
    if (!input) {
        perror("Failed to open the input PDF file for reading");
        return EXIT_FAILURE;
    }

    FILE *output = fopen(outputPath, "wb");
    if (!output) {
        perror("Failed to create the output file in uploads directory");
        fclose(input);
        return EXIT_FAILURE;
    }

    const size_t buffer_size = 4096;
    char buffer[buffer_size];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, buffer_size, input)) > 0) {
        fwrite(buffer, 1, bytes_read, output);
    }

    fclose(input);
    fclose(output);

    printf("File successfully saved to %s\n", outputPath);

    return EXIT_SUCCESS;
}