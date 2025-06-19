#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFF 256
void ping(char* url)
{
    char cmd[MAX_BUFF];
    sprintf(cmd, "ping %s", url);
    system(cmd);
}