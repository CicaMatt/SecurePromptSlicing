#include <stdio.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

void ping(const char* url) {
    char command[MAX_URL_LENGTH + 5]; // 5 for "ping " and null terminator
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    const char* url = "example.com";
    printf("Pinging URL: %s\n", url);
    ping(url);
    return 0;
}