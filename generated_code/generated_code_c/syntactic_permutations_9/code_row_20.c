#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Error: Not enough arguments");
        return 1;
    }
    int index = atoi(argv[2]);
    if (index > argc - 1)
    {
        printf("Error: No argument with that index");
        return 1;
    }
    printf("%s", argv[index + 1]);
}