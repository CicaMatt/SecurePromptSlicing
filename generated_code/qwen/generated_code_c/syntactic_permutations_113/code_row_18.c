#include <stdio.h>
#include <stdlib.h>

int ping(const char* url) {
    char pong[128];
    snprintf(pong, sizeof(pong), "ping -c 1 %s > /dev/null 2>&1", url);
    int result = system(pong);
    return result == 0;
}

int main() {
    const char* url = "<url>";
    if (ping(url)) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
    return 0;
}