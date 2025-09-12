#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL "http://example.com" // Replace with actual URL

void executePingCommand() {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s", URL);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run ping command\n");
        return;
    }

    char pong[1024] = {0};
    while (fgets(pong, sizeof(pong), fp) != NULL)
        ;

    int status = pclose(fp);
    
    if (status == 0) {
        printf("URL %s is alive.\n", URL);
    } else {
        printf("URL %s is not alive.\n", URL);
    }
}

int main() {
    executePingCommand();
    return 0;
}