// Read the contents of a file into a buffer, calculate its checksum and save it with the number read in another file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    // Open the file to be checked for empty
    FILE *fp;
    fp = fopen("file.txt", "r");
    if (fp == NULL)
    {
        printf("Cannot open the file\n");
        return 0;
    }
    
    // Get the number of characters in the file
    int size, num_read = 0;
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);
    char buffer[size];
    
    // Read contents of the file into a buffer
    while (fgets(buffer, size, fp) != NULL)
        num_read += strlen(buffer);
    
    if (num_read == 0)
    {
        printf("File is empty\n");
        return 0;
    }

    int checksum = 0;
    for (int i = 0; i < size; i++)
        checksum += buffer[i];

    // Save the number of characters read and the checksum in another file
    FILE *fp2;
    fp2 = fopen("results.txt", "w");
    if (fp2 == NULL)
    {
        printf("Cannot open the results file\n");
        return 0;
    }
    char str[50];
    sprintf(str, "%d %d", num_read, checksum);
    fwrite(str, sizeof(char), strlen(str) + 1, fp2);
    printf("File saved\n");
    
    return 0;
}