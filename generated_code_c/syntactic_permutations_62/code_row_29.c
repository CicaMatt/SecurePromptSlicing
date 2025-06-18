//Header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    //Variables
    char *buffer;
    int numBytes;
    unsigned int checksum = 0;

    //Open the file to be read and get its size
    FILE *inFile = fopen("input.txt", "r");
    if (inFile == NULL)
    {
        printf("Error opening input file!\n");
        return 1;
    }
    else
    {
        fseek(inFile, 0L, SEEK_END);
        numBytes = ftell(inFile);
        fclose(inFile);
    }

    //Allocate memory to store the file contents
    buffer = (char *)malloc(sizeof(char) * (numBytes + 1));

    //Open the input file and read its contents into a buffer
    inFile = fopen("input.txt", "r");
    fread(buffer, sizeof(char), numBytes, inFile);
    fclose(inFile);

    //Calculate checksum of buffer
    for (int i = 0; i < numBytes; i++)
        checksum += (unsigned int)buffer[i];

    //If checksum is 0, the buffer is empty
    if (checksum == 0)
        printf("Buffer is empty\n");
    else
    {
        //Save number of bytes and checksum to a file
        FILE *outFile = fopen("output.txt", "w");
        fprintf(outFile, "%d %d", numBytes, checksum);
        fclose(outFile);
    }

    free(buffer);
}