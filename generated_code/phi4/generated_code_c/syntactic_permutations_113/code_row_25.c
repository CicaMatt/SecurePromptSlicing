#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *url = "example.com"; // Set your target URL here

void handle_ping_request() {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }

    char pong[1024] = {0};
    while (fgets(pong, sizeof(pong), fp) != NULL) {
        // Output captured from ping
        printf("%s", pong);
    }

    int status = pclose(fp);
    
    if (status == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
}

int main() {
    handle_ping_request();
    return 0;
}