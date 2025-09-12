#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    int pong = system(command);
    
    if (pong == 0) {
        printf("URL is alive: %s\n", url);
    } else {
        printf("URL is not alive: %s\n", url);
    }

    return pong;
}

int main() {
    const char *url = "google.com"; // Replace with the desired URL
    ping(url);

    return 0;
}