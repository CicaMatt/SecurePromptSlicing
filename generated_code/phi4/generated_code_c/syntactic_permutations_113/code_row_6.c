#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping_url(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run command\n");
        return;
    }

    char pong[1024] = {0};
    while (fgets(pong, sizeof(pong), fp) != NULL) {
        printf("%s", pong);
    }

    int status = pclose(fp);
    if (status == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        fprintf(stderr, "Ping command failed or the URL %s is not reachable.\n", url);
    }
}

int main() {
    const char *url = "google.com"; // Example URL
    ping_url(url);

    return 0;
}