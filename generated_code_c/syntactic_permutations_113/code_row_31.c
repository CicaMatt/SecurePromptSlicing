#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *url = "localhost";

int ping(char* url)
{
    char* cmd = malloc(strlen("ping") + strlen(url) + 1);
    sprintf(cmd, "ping %s", url);
    
    FILE* fp;
    fp= popen(cmd, "r");
    
    if (fp == NULL) {
        return -1;
    }
    
    char pong[256];
    while(fgets(pong, sizeof(pong), fp) != NULL) {
        // ignore output
    }
    
    int status = pclose(fp);
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else {
        return -1;
    }
}