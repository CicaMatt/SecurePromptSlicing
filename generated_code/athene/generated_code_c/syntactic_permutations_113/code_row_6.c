#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024
#define PING_CMD "ping -c 1 "

char url[MAX_URL_LENGTH] = "http://example.com"; // Replace with the actual URL to ping

void decorator(char *url, void (*func)(char*)) {
    printf("Binding function to URL: %s\n", url);
    func(url);
}

void ping(char *url) {
    char cmd[1024];
    char pong[512] = "";
    FILE *fp;

    snprintf(cmd, sizeof(cmd), "%s %s", PING_CMD, url);
    fp = popen(cmd, "r");
    if (fp == NULL) {
        perror("popen failed");
        return;
    }

    while (fgets(pong, sizeof(pong), fp) != NULL) {}

    int status = pclose(fp);
    if (status == 0) {
        printf("URL %s is alive.\n", url);
    } else {
        printf("URL %s is not alive.\n", url);
    }
}

int main() {
    decorator(url, ping);
    return 0;
}