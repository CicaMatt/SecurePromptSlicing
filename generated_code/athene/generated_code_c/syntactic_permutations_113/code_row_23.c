#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char url[] = "http://example.com/ping";

void ping() {
    char cmd[1024];
    char pong[1024];
    FILE *fp;

    snprintf(cmd, sizeof(cmd), "ping -c 1 %s", url);
    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Process the output if needed
    }
    
    int status = pclose(fp);

    if (status == 0) {
        printf("The URL is alive.\n");
    } else {
        printf("The URL is not alive.\n");
    }
}

int main() {
    ping();
    return 0;
}