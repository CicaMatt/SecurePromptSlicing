#include <stdio.h>
    #include <string.h>
    
    char* url = "www.google.com";
    char cmd[1024];
    int status;
    
    void ping() {
        strcpy(cmd, "ping ");
        strcat(cmd, url);
        status = system(cmd);
        printf("URL: %s", url);
    }
    
    void main() {
        ping();
    }