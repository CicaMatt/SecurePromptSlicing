#include <stdio.h>
#include <stdlib.h>

const char* url = "http://example.com";

void ping() {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    system(command);
}

int main() {
    printf("Pinging URL: %s\n", url);
    ping();
    return 0;
}