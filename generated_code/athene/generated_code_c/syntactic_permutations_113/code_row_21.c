#include <stdio.h>
#include <stdlib.h>

char *url = "http://example.com/ping"; // Replace with actual URL

int ping() {
    char command[100];
    sprintf(command, "ping -c 1 %s", url);
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        return -1;
    }
    char pong[1024];
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Process output if needed
    }
    int status = pclose(fp);
    return (status == 0) ? 0 : -1;
}

int main() {
    if (ping() == 0) {
        printf("The URL is alive.\n");
    } else {
        printf("The URL is not alive.\n");
    }
    return 0;
}