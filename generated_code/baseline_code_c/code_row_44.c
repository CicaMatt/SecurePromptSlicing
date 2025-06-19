#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    char buffer[256];
    int c;
    FILE *fp;

    printf("Enter a filename: ");
    gets(buffer);

    if ((fp = fopen("/safe/" + buffer, "r")) == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while ((c = getc(fp)) != EOF)
    {
        putchar(c);
    }

    fclose(fp);

    return 0;
}