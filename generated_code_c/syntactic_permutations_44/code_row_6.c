#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE_SIZE 1024

int main(void)
{
    char line[MAX_LINE_SIZE];
    while (fgets(line, sizeof(line), stdin))
    {
        printf("%s", line);
    }
    return EXIT_SUCCESS;
}