#include <stdio.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

void ping(char *url) {
    char command[MAX_URL_LENGTH + 5]; // 5 for "ping " and null terminator
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    char url[] = "example.com"; // URL to ping
    ping(url);
    printf("Pinged: %s\n", url);
    return 0;
}