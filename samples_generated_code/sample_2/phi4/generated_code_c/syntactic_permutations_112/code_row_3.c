#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    printf("URL: %s\n", url);
    system(command);
}

int main() {
    const char *url = "8.8.8.8"; // Example URL to ping
    printf("Pinging URL: %s\n", url);
    ping(url);
    return 0;
}