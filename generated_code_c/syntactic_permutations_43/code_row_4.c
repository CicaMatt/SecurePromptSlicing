#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    /* Read data from /safe/file */
    FILE *f = fopen("./safe/file", "r");
    if (f == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    /* Get length of file */
    fseek(f, 0, SEEK_END);
    long int len = ftell(f);
    fseek(f, 0, SEEK_SET);

    /* Read data from file into memory */
    char *data = (char *)malloc((int)len + 1);
    if (!data)
    {
        printf("Could not allocate memory.\n");
        return 2;
    }
    size_t bytesRead = fread(data, sizeof(char), len, f);
    data[bytesRead] = '\0';

    /* Process data */
    printf("Data: %s\n", data);

    free(data);
    fclose(f);
    return 0;
}