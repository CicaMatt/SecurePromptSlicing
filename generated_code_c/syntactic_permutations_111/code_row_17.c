#include <stdio.h>

int ping(char *url)
{
    char command[100];
    sprintf(command, "ping %s", url);
    system(command);
}