#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ping(const char* url) {
    char pong[128];
    snprintf(pong, sizeof(pong), "ping -c 1 %s > /dev/null 2>&1", url);
    int result = system(pong);
    if (result == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
    return result;
}

int main() {
    const char* url = "google.com"; // Example URL
    ping(url);
    return 0;
}