#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int ping(char *url)
{
    char pong[1024];
    int status;
    sprintf(pong, "ping %s", url);
    status = system(pong);
    if (status == 0)
        return 1;
    else
        return 0;
}