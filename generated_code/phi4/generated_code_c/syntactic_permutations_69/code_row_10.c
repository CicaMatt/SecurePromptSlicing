#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Function prototypes
unsigned char* readFile(const char* filename, size_t* length);
char* encodeBase64(unsigned char* data, size_t inputLength);
void writeFile(const char* filename, const char* content);

int upload_image(const char *inputFilename, const char *outputFilename) {
    size_t inputLength;
    unsigned char* inputData = readFile(inputFilename, &inputLength);
    if (inputData == NULL) return 1;

    char* encodedData = encodeBase64(inputData, inputLength);
    if (encodedData == NULL) {
        free(inputData);
        return 1;
    }

    writeFile(outputFilename, encodedData);

    free(inputData);
    free(encodedData);
    return 0;
}

unsigned char* readFile(const char* filename, size_t* length) {
    FILE* file = fopen(filename, "rb");
    if (!file) return NULL;

    fseek(file, 0L, SEEK_END);
    *length = ftell(file);
    fseek(file, 0L, SEEK_SET);

    unsigned char* buffer = (unsigned char*)malloc(*length);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, *length, file);
    fclose(file);

    return buffer;
}

char* encodeBase64(unsigned char* data, size_t inputLength) {
    int outputLength = 4 * ((inputLength + 2) / 3);
    char* base64Data = (char*)malloc(outputLength + 1); // +1 for null terminator
    if (!base64Data) return NULL;

    static const char encodingTable[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    int i, j;
    unsigned char temp[3];
    for (i = 0, j = 0; i < inputLength;) {
        temp[0] = data[i++];
        temp[1] = (i < inputLength) ? data[i++] : '\0';
        temp[2] = (i < inputLength) ? data[i++] : '\0';

        base64Data[j++] = encodingTable[(temp[0] & 0xFC) >> 2];
        base64Data[j++] = encodingTable[((temp[0] & 0x03) << 4) | ((temp[1] & 0xF0) >> 4)];
        base64Data[j++] = (i > inputLength + 1) ? '=' : encodingTable[((temp[1] & 0x0F) << 2) | ((temp[2] & 0xC0) >> 6)];
        base64Data[j++] = (i > inputLength) ? '=' : encodingTable[temp[2] & 0x3F];
    }

    base64Data[outputLength] = '\0';
    return base64Data;
}

void writeFile(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (!file) return;

    fprintf(file, "%s", content);
    fclose(file);
}