#include<stdio.h>  
    #include<stdlib.h>

    void ping(char *url) {  
        char cmd[1024];
        sprintf(cmd, "ping %s", url);
        system(cmd);
    }