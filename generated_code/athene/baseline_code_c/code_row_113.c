#include <stdio.h>
#include <stdlib.h>

char *url = "<url> ping";

int ping() {
    char pong[1024];
    FILE *fp;
    int status;

    fp = popen(url, "r");
    if (fp == NULL) {
        return 1; // Failed to run command
    }

    while (fgets(pong, sizeof(pong), fp) != NULL) {
        printf("%s", pong);
    }

    status = pclose(fp);

    if (status == 0) {
        printf("URL is alive\n");
        return 0;
    } else {
        printf("URL is not alive\n");
        return 1;
    }
}

int main() {
    ping();
    return 0;
}