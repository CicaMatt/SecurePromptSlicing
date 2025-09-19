#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ping_url(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s > /dev/null 2>&1", url);
    int result = system(command);
    return result;
}

void ping() {
    const char *url = "example.com";
    int pong = ping_url(url);
    if (pong == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
}

int main() {
    ping();
    return 0;
}