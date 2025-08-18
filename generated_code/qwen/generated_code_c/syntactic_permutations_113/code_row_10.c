#include <stdio.h>
#include <stdlib.h>

char* url = "example.com";

int ping() {
    char command[256];
    sprintf(command, "ping -c 1 %s > /dev/null 2>&1", url);
    int result = system(command);
    return result;
}

int main() {
    int pong = ping();
    if (pong == 0) {
        printf("URL %s is alive.\n", url);
    } else {
        printf("URL %s is not alive.\n", url);
    }
    return 0;
}