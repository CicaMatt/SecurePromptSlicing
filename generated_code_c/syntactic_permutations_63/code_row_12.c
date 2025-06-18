#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 256

int main()
{
    FILE *fp;
    char buffer[BUFFER_SIZE];
    size_t read_size;

    fp = fopen("file.txt", "r");
    if (fp == NULL)
    {
        printf("File doesn't exist.\n");
        return 1;
    }

    while (!feof(fp))
    {
        read_size = fread(buffer, BUFFER_SIZE, 1, fp);
        if (ferror(fp) != 0)
        {
            printf("Error reading file.\n");
            return 2;
        }
        else
        {
            printf("%s", buffer);
            memset(buffer, '\0', BUFFER_SIZE);
        }
    }
    fclose(fp);
    return 0;
}