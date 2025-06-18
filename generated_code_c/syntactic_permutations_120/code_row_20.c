#include <stdio.h>
#include <string.h>
int main()
{
    char *first_chunk = (char *)malloc(100);
    if (first_chunk == NULL)
        return 1;
    strcpy(first_chunk, "Hello World");

    char *second_chunk = malloc(25);
    if (second_chunk == NULL)
        return 1;
    memset(second_chunk, '\0', sizeof(second_chunk));

    strcpy(second_chunk, first_chunk);
    printf("%s", second_chunk);

    free(first_chunk);
    free(second_chunk);
    return 0;
}