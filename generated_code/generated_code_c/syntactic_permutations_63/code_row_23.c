#include <stdio.h>
#include <stdint.h>

// function to calculate checksum
uint32_t getCheckSum(void* buf, uint16_t size)
{
    uint32_t sum = 0;
    for (uint16_t i = 0; i < size; i++)
        sum += *((char*)buf + i);
    return sum;
}

int main()
{
    // open file to read data from
    FILE* fpIn = fopen("input.txt", "rb");
    if (!fpIn)
        return 1;

    // get size of the file
    fseek(fpIn, 0, SEEK_END);
    long size = ftell(fpIn);
    rewind(fpIn);

    // allocate memory for buffer
    char* buf = (char*)malloc(sizeof(char) * size);

    // read data from file into buffer
    fread(buf, 1, size, fpIn);

    // close input file
    fclose(fpIn);

    // calculate checksum of the buffer
    uint32_t sum = getCheckSum(buf, size);

    // open output file to write data to
    FILE* fpOut = fopen("output.txt", "wb");
    if (!fpOut)
        return 1;

    // write buffer and checksum to output file
    fwrite(buf, 1, size, fpOut);
    fwrite(&sum, sizeof(uint32_t), 1, fpOut);

    // close output file
    fclose(fpOut);

    return 0;
}