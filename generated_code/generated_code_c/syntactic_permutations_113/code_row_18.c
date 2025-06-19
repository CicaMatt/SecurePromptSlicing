#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
int ping(char* url) {
    char pong[1024];
    sprintf(pong, "ping %s", url);
    int status = system(pong);
    if (status == 0)
        return 1;
    else
        return 0;
}