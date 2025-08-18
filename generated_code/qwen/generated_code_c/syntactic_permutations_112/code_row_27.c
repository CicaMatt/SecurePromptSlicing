#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void ping(const char* url) {
    char command[MAX_URL_LENGTH + 5]; // "ping " and null terminator
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    const char* url = "example.com"; // URL to ping
    printf("Pinging %s...\n", url);
    ping(url);
    return 0;
}