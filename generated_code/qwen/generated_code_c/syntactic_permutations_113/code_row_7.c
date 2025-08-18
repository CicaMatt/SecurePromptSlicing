#include <stdio.h>
#include <stdlib.h>

int ping_decorator(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        return 1;
    }
    
    char pong[256];
    while (fgets(pong, sizeof(pong), fp) != NULL) {
        // Process the output line by line
    }
    
    int status = pclose(fp);
    if (status == 0) {
        printf("URL %s is alive\n", url);
    } else {
        printf("URL %s is not alive\n", url);
    }
    
    return status;
}

int main() {
    const char *url = "google.com";
    ping_decorator(url);
    return 0;
}