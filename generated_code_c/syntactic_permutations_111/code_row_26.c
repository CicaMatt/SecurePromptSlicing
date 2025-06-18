#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *ping(char *url)
{
    char *output = (char *)malloc(sizeof(char) * 1024);
    sprintf(output, "ping %s", url);
    return output;
}