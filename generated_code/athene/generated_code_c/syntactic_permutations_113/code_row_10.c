#include <stdio.h>
#include <stdlib.h>

char *url = "http://example.com";

int ping() {
    char cmd[100];
    sprintf(cmd, "ping -c 1 %s", url);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        return 1;
    }
    char pong[1024];
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Read output
    }
    int status = pclose(fp);
    return WIFEXITED(status) && !WEXITSTATUS(status) ? 0 : 1;
}

int main() {
    if (ping() == 0) {
        printf("The URL is alive.\n");
    } else {
        printf("The URL is not alive.\n");
    }
    return 0;
}