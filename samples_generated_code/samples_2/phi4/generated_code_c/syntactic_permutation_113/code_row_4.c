#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping(const char *url) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ping -c 1 %s", url);

    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }

    char pong[1024] = {0};
    while (fgets(pong, sizeof(pong), fp) != NULL) {
        if (strstr(pong, "1 packets transmitted") && strstr(pong, "1 received")) {
            printf("URL %s is alive\n", url);
        } else {
            printf("URL %s is not reachable\n", url);
        }
    }

    int status = pclose(fp);
    if (status == -1) {
        printf("Failed to close pipe\n");
    } else {
        // Check the exit status of the ping command
        if (WIFEXITED(status)) {
            int ret_status = WEXITSTATUS(status);
            if (ret_status == 0) {
                printf("Ping successful: URL %s is alive\n", url);
            } else {
                printf("Ping failed: URL %s might be down or unreachable\n", url);
            }
        }
    }
}

int main() {
    const char *url = "google.com";
    ping(url);
    return 0;
}