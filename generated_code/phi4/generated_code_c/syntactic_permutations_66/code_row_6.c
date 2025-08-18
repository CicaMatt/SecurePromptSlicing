#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_pdf_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *inputFile = argv[1];
    const char *outputDir = "./uploads/";

    // Ensure the output directory exists
    FILE *check_dir = fopen(outputDir, "a");
    if (check_dir) {
        fclose(check_dir);
    } else {
        mkdir(outputDir, 0777);
    }

    const char *outputFile = outputDir "saved_file.pdf";

    FILE *in = fopen(inputFile, "rb");
    if (!in) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    FILE *out = fopen(outputFile, "wb");
    if (!out) {
        perror("Error creating output file");
        fclose(in);
        return EXIT_FAILURE;
    }

    char buffer[1024];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), in)) > 0) {
        fwrite(buffer, 1, bytesRead, out);
    }

    fclose(in);
    fclose(out);

    printf("PDF file saved to %s\n", outputFile);
    
    return EXIT_SUCCESS;
}