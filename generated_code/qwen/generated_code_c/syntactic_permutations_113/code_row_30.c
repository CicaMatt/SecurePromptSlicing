#include <stdio.h>
#include <stdlib.h>

int ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s > /dev/null 2>&1", url);
    int result = system(command);
    if (result == 0) {
        printf("URL is alive.\n");
    } else {
        printf("URL is not reachable.\n");
    }
    return result;
}

int main() {
    const char* url = "example.com";
    ping(url);
    return 0;
}