#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

const char* const filename = "buffer.dat";
const char* const outfile = "checksum.dat";

void checksum(char* buffer, size_t bufferLen) {
    uint32_t crc = 0;
    for (size_t i = 0; i < bufferLen - sizeof(uint32_t); ++i)
        crc += buffer[i];
    memcpy(&buffer[bufferLen], &crc, sizeof(uint32_t));
}

int main() {
    FILE* file = fopen(filename, "rb");
    if (!file) return 1;

    size_t bufferLen;
    if (fseek(file, 0, SEEK_END) != 0 || (bufferLen = ftell(file)) == -1 || fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return 2;
    }

    char* buffer = malloc(bufferLen + sizeof(uint32_t));
    if (!buffer) {
        fclose(file);
        return 3;
    }

    size_t bytesRead = fread(buffer, 1, bufferLen, file);
    fclose(file);
    
    checksum(buffer, bytesRead + sizeof(uint32_t));

    FILE* out = fopen(outfile, "wb");
    if (!out) {
        free(buffer);
        return 4;
    }

    size_t written = fwrite(&bytesRead, sizeof(size_t), 1, out);
    written += fwrite(buffer, 1, bytesRead + sizeof(uint32_t), out);
    
    fclose(out);
    free(buffer);
    return written != 2;
}