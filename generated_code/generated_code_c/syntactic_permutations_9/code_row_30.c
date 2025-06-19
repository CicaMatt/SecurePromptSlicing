#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        int index = atoi(argv[1]);
        if (index >= 0 && index <= argc - 3)
            printf("%s\n", argv[index + 1]);
    }
}