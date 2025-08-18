#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s > /dev/null 2>&1", url);
    int result = system(command);
    return result == 0;
}

void handle_request(const char* request_url) {
    if (strcmp(request_url, "ping") == 0) {
        const char* url = "example.com"; // URL to ping is stored here
        int is_alive = ping(url);
        const char* pong = is_alive ? "URL is alive" : "URL is not alive";
        printf("%s\n", pong);
    } else {
        printf("Unknown request\n");
    }
}

int main() {
    const char* url = "ping"; // Simulating the URL request
    handle_request(url);
    return 0;
}