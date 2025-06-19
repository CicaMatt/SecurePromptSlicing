#include <stdio.h>
#include <stdlib.h>

int get_index(char **argv)
{
    int i = atoi(argv[1]); // atoi converts string to integer
    return argv[i];        // returns the value at index i
}