#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 256
int main(void)
{
    //opening the file
    FILE* fp;
    fp = fopen("file.txt", "r");

    if (!fp)
    {
        printf("Could not open file\n");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    int bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, fp);

    //checking for checksum
    unsigned int checkSum = 0;
    int i;
    for (i = 0; i < bytesRead; i++)
        checkSum += buffer[i];
    if (checkSum == 0)
    {
        printf("Buffer is empty\n");
    }
    else
    {
        printf("Checksum is %d\n", checkSum);
    }

    //printing the number of bytes read and buffer contents
    printf("%d\n", bytesRead);
    for (i = 0; i < bytesRead; i++)
        printf("%c", buffer[i]);

    return 0;
}