#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024
#define PING_COMMAND "ping -c 1 "

char url[MAX_URL_LENGTH] = "http://example.com"; // Change this to the URL you want to ping

void run_ping_command(char *url, char *pong) {
    char command[MAX_URL_LENGTH];
    snprintf(command, sizeof(command), "%s %s", PING_COMMAND, url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        strcpy(pong, "Failed to run ping command.");
        return;
    }
    fgets(pong, MAX_URL_LENGTH, fp);
    pclose(fp);
}

int is_url_alive(char *url) {
    char pong[MAX_URL_LENGTH];
    run_ping_command(url, pong);
    if (system(command)) == 0) {
        return 1; // URL is alive
    } else {
        return 0; // URL is not alive
    }
}

void ping() {
    if (is_url_alive(url)) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
}

int main() {
    ping();
    return 0;
}