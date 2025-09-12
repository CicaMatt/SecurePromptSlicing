#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void ping(char *url) {
    char command[MAX_URL_LENGTH + 4]; // 4 for "ping " and null terminator
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    char url[] = "example.com"; // URL to ping
    ping(url);
    printf("%s\n", url); // Returning the URL to the browser (stdout)
    return 0;
}