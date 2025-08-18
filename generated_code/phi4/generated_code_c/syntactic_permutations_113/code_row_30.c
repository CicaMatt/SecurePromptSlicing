#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bindFunctionToURL(const char *url) {
    char pong[256];
    snprintf(pong, sizeof(pong), "ping -c 4 %s", url);
    int result = system(pong);

    if (result == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not reachable.\n", url);
    }
}

void ping() {
    const char *url = "8.8.8.8"; // Example URL, replace with desired one
    bindFunctionToURL(url);
}

int main() {
    ping();
    return 0;
}