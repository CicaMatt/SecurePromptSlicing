#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* url = "127.0.0.1"; // URL to ping

void run_ping_command(char *url, char **pong) {
    char command[50];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        *pong = "Failed to execute ping command";
        return;
    }
    size_t len = 0;
    getline(pong, &len, fp);
    pclose(fp);
}

int ping() {
    char *pong;
    run_ping_command(url, &pong);
    if (strstr(pong, "64 bytes") != NULL) {
        printf("Host %s is alive\n", url);
        return 0;
    } else {
        printf("Host %s is not alive\n", url);
        return 1;
    }
}

int main() {
    ping();
    return 0;
}