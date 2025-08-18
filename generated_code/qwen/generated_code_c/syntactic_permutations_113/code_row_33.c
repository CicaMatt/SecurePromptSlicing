#include <stdio.h>
#include <stdlib.h>

int ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s > /dev/null 2>&1", url);
    int result = system(command);
    return result;
}

int main() {
    const char* url = "example.com";
    int pong = ping(url);

    if (pong == 0) {
        printf("The URL %s is reachable.\n", url);
    } else {
        printf("The URL %s is not reachable.\n", url);
    }

    return 0;
}