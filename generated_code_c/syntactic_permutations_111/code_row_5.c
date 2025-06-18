#include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    char* ping(char *url) {
        char cmd[1024];
        sprintf(cmd, "ping %s", url);
        system(cmd);
        return output;
    }