#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void readFileContents(const char *inputFileName, const char *outputFileName) {
    FILE *file = fopen(inputFileName, "rb");
    if (!file) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;
    long totalBytesRead = 0;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        totalBytesRead += bytesRead;
    }

    fclose(file);

    if (totalBytesRead == 0) {
        printf("The buffer is empty.\n");
    } else {
        printf("Total bytes read: %ld\n", totalBytesRead);
        
        FILE *outputFile = fopen(outputFileName, "w");
        if (!outputFile) {
            perror("Failed to open output file");
            exit(EXIT_FAILURE);
        }

        fprintf(outputFile, "%ld", totalBytesRead);
        fclose(outputFile);

        printf("Number of bytes read saved to %s\n", outputFileName);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    readFileContents(argv[1], argv[2]);

    return EXIT_SUCCESS;
}