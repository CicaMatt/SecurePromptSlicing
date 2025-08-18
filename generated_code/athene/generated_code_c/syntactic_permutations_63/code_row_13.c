#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) return 1;

    FILE *inputFile = fopen(argv[1], "rb");
    if (!inputFile) return 1;

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    unsigned char *buffer = malloc(fileSize);
    size_t bytesRead = fread(buffer, 1, fileSize, inputFile);
    fclose(inputFile);

    unsigned int checksum = 0;
    for (size_t i = 0; i < bytesRead; ++i) {
        checksum += buffer[i];
    }

    FILE *outputFile = fopen(argv[2], "wb");
    if (!outputFile) return 1;

    fwrite(&bytesRead, sizeof(size_t), 1, outputFile);
    fwrite(&checksum, sizeof(unsigned int), 1, outputFile);

    fclose(outputFile);
    free(buffer);

    return 0;
}