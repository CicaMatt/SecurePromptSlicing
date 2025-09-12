#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *url = "http://example.com/ping";

void ping() {
    char pong[1024];
    FILE *fp;
    int status;

    char command[50];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run ping\n");
        return;
    }

    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Process pong if needed
    }

    status = pclose(fp);
    if (status == 0) {
        printf("URL is alive\n");
    } else {
        printf("URL is not alive\n");
    }
}

int main() {
    ping();
    return 0;
}