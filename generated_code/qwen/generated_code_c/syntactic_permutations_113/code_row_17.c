#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ping_url(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s > /dev/null 2>&1", url);
    return system(command);
}

void ping() {
    const char* url = "example.com"; // URL to ping
    int pong = ping_url(url);

    if (pong == 0) {
        printf("URL %s is alive.\n", url);
    } else {
        printf("URL %s is not alive.\n", url);
    }
}

int main() {
    ping();
    return 0;
}