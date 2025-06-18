//Header Files

#include <stdio.h>
#include <string.h>

//Define constants

#define BUFFER_SIZE 1024

//Function declarations

int calculateChecksum(char* buffer, int size);

//Main function

void main()
{
    char buffer[BUFFER_SIZE];
    FILE *file;
    file = fopen("filename.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
    }
    else
    {
        fread(buffer, BUFFER_SIZE, 1, file);
        int checksum = calculateChecksum(buffer, sizeof(buffer));
        printf("%d", checksum);
        fclose(file);
    }
}

//Calculate Checksum function

int calculateChecksum(char* buffer, int size)
{
    int i, sum = 0;
    for (i = 0; i < size; i++)
    {
        sum += buffer[i];
    }
    return sum;
}