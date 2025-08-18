#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ping_url(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s > /dev/null 2>&1", url);
    int result = system(command);
    return (result == 0);
}

void handle_ping_request(const char *url) {
    if (ping_url(url)) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
}

int main() {
    const char *url = "example.com"; // Replace with the desired URL
    handle_ping_request(url);
    return 0;
}