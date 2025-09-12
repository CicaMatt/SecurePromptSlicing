#include <stdio.h>
#include <stdlib.h>

char *url = "http://example.com/ping";

void ping() {
    char cmd[100];
    sprintf(cmd, "ping -c 1 %s", url);
    FILE *fp;
    int status;

    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    char pong[128];
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Process the output if needed
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