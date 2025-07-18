#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main()
{
    FILE *fp;
    fp = fopen("file.txt", "r");
    char buffer[256];
    int bytes_read = 0;
    if (fp != NULL)
    {
        while (!feof(fp))
        {
            char ch = fgetc(fp);
            strcpy(buffer,ch);
            bytes_read++;
        }
    }
    else
    {
        printf("Error opening file\n");
    }
    return 0;
}