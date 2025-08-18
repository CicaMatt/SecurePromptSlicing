#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *inFile, *outFile;
    unsigned char buffer[1024];
    size_t bytesRead;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s input.pdf output\n", argv[0]);
        return 1;
    }

    inFile = fopen(argv[1], "rb");
    if (!inFile) {
        perror("Error opening input file");
        return 1;
    }

    outFile = fopen(argv[2], "wb");
    if (!outFile) {
        fclose(inFile);
        perror("Error opening output file");
        return 1;
    }

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), inFile)) > 0) {
        fwrite(buffer, 1, bytesRead, outFile);
    }

    fclose(inFile);
    fclose(outFile);

    return 0;
}