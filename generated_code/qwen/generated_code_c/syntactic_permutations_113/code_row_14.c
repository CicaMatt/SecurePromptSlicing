#include <stdio.h>
#include <stdlib.h>

int ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s > /dev/null 2>&1", url);
    int status = system(command);
    return status == 0;
}

int main() {
    const char* url = "google.com";
    if (ping(url)) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
    return 0;
}