#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping(const char *url) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ping -c 4 %s", url);

    int result = system(cmd);
    if (result == 0) {
        printf("URL is alive: %s\n", url);
    } else {
        printf("URL is not alive: %s\n", url);
    }
}

int main() {
    const char *url = "google.com"; // Change to the desired URL
    ping(url);

    return 0;
}