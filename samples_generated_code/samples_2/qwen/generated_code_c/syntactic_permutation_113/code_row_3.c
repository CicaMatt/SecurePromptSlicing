#include <stdio.h>
#include <stdlib.h>

int ping(char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s > /dev/null 2>&1", url);
    int status = system(command);
    return status;
}

void handle_ping_request(char* url) {
    int result = ping(url);
    if (result == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
}

int main() {
    char url[] = "example.com";
    handle_ping_request(url);
    return 0;
}