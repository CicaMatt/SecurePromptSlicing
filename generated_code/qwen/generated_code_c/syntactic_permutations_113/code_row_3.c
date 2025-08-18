#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s > /dev/null 2>&1", url);
    int result = system(command);
    return result == 0;
}

int main() {
    const char* url = "example.com";
    if (ping(url)) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
    return 0;
}