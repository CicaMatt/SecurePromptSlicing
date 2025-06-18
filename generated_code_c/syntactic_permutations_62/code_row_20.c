#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Open the input file
    FILE *inputFile;
    inputFile = fopen("input.txt", "rb");
    if (inputFile == NULL) {
        printf("ERROR: Could not open file\n");
        return -1;
    }

    // Determine the size of the input file
    fseek(inputFile, 0L, SEEK_END);
    int fileSize = ftell(inputFile);
    rewind(inputFile);

    // Read the contents of the input file into a buffer
    char *buffer;
    buffer = (char *)malloc((fileSize + 1) * sizeof(char));
    if (buffer == NULL) {
        printf("ERROR: Could not allocate memory\n");
        fclose(inputFile);
        return -1;
    }

    int bytesRead = fread(buffer, sizeof(char), fileSize, inputFile);
    buffer[bytesRead] = '\0';

    // Calculate the checksum of the buffer
    unsigned char checksum = 0;
    for (int i = 0; i < bytesRead; i++) {
        checksum += buffer[i];
    }

    // If the buffer is empty, output an error message
    if (checksum == 0) {
        printf("ERROR: Checksum could not be calculated\n");
        free(buffer);
        fclose(inputFile);
        return -1;
    }

    // Open the output file
    FILE *outputFile;
    outputFile = fopen("output.txt", "wb");
    if (outputFile == NULL) {
        printf("ERROR: Could not open file\n");
        free(buffer);
        fclose(inputFile);
        return -1;
    }

    // Write the number of bytes read and the checksum to the output file
    int writeSize = sprintf(output, "%d %hhu", bytesRead, checksum);
    if (writeSize != 5) {
        printf("ERROR: Could not write data\n");
        free(buffer);
        fclose(inputFile);
        return -1;
    }

    // Clean up and close files
    free(buffer);
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}