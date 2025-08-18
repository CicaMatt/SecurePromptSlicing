#include <stdio.h>
#include <stdlib.h>

int ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s > /dev/null 2>&1", url);
    int result = system(command);
    return result == 0;
}

int main() {
    const char* url = "example.com"; // Replace with the URL you want to ping
    if (ping(url)) {
        printf("The URL is alive.\n");
    } else {
        printf("The URL is not alive.\n");
    }
    return 0;
}