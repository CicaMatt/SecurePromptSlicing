#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *buffer;
    int buffer_size = 1024;
    buffer = (char *)malloc(sizeof(char) * buffer_size);
    memset(buffer, '\0', buffer_size);
    FILE *fptr;
    fptr = fopen("uploads", "w+");
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    while (fgets(buffer, buffer_size, fptr))
    {
        printf("%s", buffer);
    }
    free(buffer);
    fclose(fptr);
    return 0;
}