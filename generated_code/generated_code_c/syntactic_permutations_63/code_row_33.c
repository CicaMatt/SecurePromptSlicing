#include <stdio.h>
#include <stdlib.h>
#define CHECKSUM 0
int main(void)
{
    char *buffer = NULL;
    int file_size, checksum = 0, bytes_read;
    FILE *file;
    file = fopen("filename", "r");
    if (file == NULL)
        exit(1);
    fseek(file, 0L, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    buffer = calloc(file_size + 1, sizeof(char));
    if (buffer == NULL)
        exit(1);
    bytes_read = fread(buffer, file_size, 1, file);
    fclose(file);
    for (int i = 0; i < bytes_read; i++)
        checksum += buffer[i];
    if (checksum == CHECKSUM)
    {
        printf("Checksum is %d\n", checksum);
        return 1;
    }
    else
    {
        printf("Buffer is not empty");
        return 0;
    }
}