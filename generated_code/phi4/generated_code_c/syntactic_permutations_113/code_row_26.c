#include <stdio.h>
#include <stdlib.h>

void ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command\n");
        return;
    }

    int status = pclose(fp);
    char pong[] = "pong";

    if (status == 0) {
        printf("%s is alive.\n", pong);
    } else {
        printf("%s is not alive.\n", pong);
    }
}

int main() {
    const char* url = "google.com"; // Example URL
    ping(url);

    return 0;
}