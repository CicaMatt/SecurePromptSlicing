#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    fp = fopen("important_config", "w");
    if (fp == NULL)
    {
        printf("File could not be opened.");
        exit(1);
    }

    fputs("important_config", fp);
    fclose(fp);
}