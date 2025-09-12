#include <stdio.h>
#include <stdlib.h>

void ping() {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    const char* url = "example.com"; // URL to ping
    printf("Pinging: %s\n", url);
    ping();
    return 0;
}