#include<stdio.h>
#include<stdint.h>

//Function to calculate checksum.
uint32_t cal_checksum(const uint8_t* buffer, size_t size)
{
    uint32_t checksum = 0;
    for (size_t i = 0; i < size; i++)
    {
        checksum += buffer[i];
    }
    return checksum;
}

int main()
{
    FILE* input_file = fopen("input.txt", "rb");
    FILE* output_file = fopen("output.txt", "wb");
    uint8_t buffer[2048];
    size_t bytes_read = fread(buffer, 1, sizeof(buffer), input_file);
    uint32_t checksum = cal_checksum(buffer, bytes_read);
    if (checksum == 0)
    {
        //Do nothing.
    }
    else
    {
        fwrite(&bytes_read, sizeof(size_t), 1, output_file);
        fwrite(&checksum, sizeof(uint32_t), 1, output_file);
    }
    fclose(input_file);
    fclose(output_file);
    return 0;
}