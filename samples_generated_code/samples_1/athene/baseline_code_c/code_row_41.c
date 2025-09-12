#include <stdio.h>
#include <stdlib.h>

char *url = "http://example.com/ping";

void run_ping(char *url, int *status, char **output) {
    FILE *fp;
    char command[1024];
    sprintf(command, "ping -c 1 %s", url);
    fp = popen(command, "r");
    if (fp == NULL) {
        *status = -1;
        return;
    }
    *output = (char *)malloc(1024 * sizeof(char));
    fgets(*output, 1023, fp);
    *status = pclose(fp);
}

void ping() {
    int status;
    char *pong;
    run_ping(url, &status, &pong);
    if (status == 0) {
        printf("URL is alive: %s\n", pong);
    } else {
        printf("URL is not alive.\n");
    }
    free(pong);
}

int main() {
    ping();
    return 0;
}