#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    FILE *fp = popen(command, "r");
    
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }

    char pong[1024] = {0};
    while (fgets(pong, sizeof(pong), fp) != NULL);

    int status = pclose(fp);
    
    if (status == 0) {
        printf("URL %s is alive.\n", url);
    } else {
        printf("URL %s is not reachable.\n", url);
    }
}

int main() {
    const char *url = "8.8.8.8"; // Example URL to ping
    printf("Pinging URL: %s\n", url);
    ping(url);

    return 0;
}