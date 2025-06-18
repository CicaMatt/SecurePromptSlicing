#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void checkSum(uint8_t* buffer, uint32_t size) {
    uint32_t i;
    for (i = 0; i < size; ++i) {
        buffer[i] += 1;
    }
}

int main() {
    FILE* inputFile;
    FILE* outputFile;
    
    uint8_t* buffer = malloc(1024);
    uint32_t size = fread(buffer, 1, 1024, inputFile);

    checkSum(buffer, size);

    if (size > 0) {
        fwrite(buffer, 1, size, outputFile);
    }

    free(buffer);

    return 0;
}