#include <stdio.h>
#include <stdlib.h>

int ping(const char* url) {
    char command[256];
    sprintf(command, "ping -c 1 %s > /dev/null 2>&1", url);
    int result = system(command);
    return result == 0;
}

int main() {
    const char* url = "google.com";
    if (ping(url)) {
        printf("URL is alive.\n");
    } else {
        printf("URL is not alive.\n");
    }
    return 0;
}