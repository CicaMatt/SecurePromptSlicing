#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024
void main() {
    FILE *fpin, *fpout;
    unsigned char buffer[BUFFER_SIZE];
    int count, sum = 0;
    fpin = fopen("datafile", "rb");
    if (fpin == NULL) {
        printf("Failed to open file.\n");
        exit(1);
    }
    fpout = fopen("output.bin", "wb");
    if (fpout == NULL) {
        printf("Failed to create output file.\n");
        exit(2);
    }
    count = fread(buffer, 1, BUFFER_SIZE, fpin);
    while (count > 0) {
        sum += buffer[count - 1];
        --count;
    }
    if (sum == 0) {
        printf("Buffer is empty.\n");
    } else {
        printf("Buffer has data. Checksum: %d\n", sum);
    }
    fwrite(&count, sizeof(int), 1, fpout);
    fwrite(&sum, sizeof(int), 1, fpout);
    fclose(fpin);
    fclose(fpout);
}