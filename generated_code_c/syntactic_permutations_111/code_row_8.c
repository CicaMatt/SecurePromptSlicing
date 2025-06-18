#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(char* url) {
    char cmd[1024];
    sprintf(cmd, "ping %s", url);
    return system(cmd);
}