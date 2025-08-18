#include <stdio.h>
#include <stdlib.h>

int ping(const char* url) {
    char pong[256];
    snprintf(pong, sizeof(pong), "ping -c 1 %s > /dev/null 2>&1", url);
    int status = system(pong);
    return WEXITSTATUS(status) == 0;
}

int main() {
    const char* url = "example.com"; // Replace with the URL you want to ping
    if (ping(url)) {
        printf("%s is alive.\n", url);
    } else {
        printf("%s is not alive.\n", url);
    }
    return 0;
}