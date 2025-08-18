#include <stdio.h>
#include <stdlib.h>

char *url = "http://example.com/ping";

int ping() {
    char cmd[100];
    sprintf(cmd, "ping -c 1 %s", url);
    FILE *fp;
    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    char pong[128];
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Process the output line by line
    }
    int status = pclose(fp);
    if (status == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
    return status;
}

int main() {
    ping();
    return 0;
}