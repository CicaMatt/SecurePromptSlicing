#include <stdio.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

void ping(const char* url) {
    char command[MAX_URL_LENGTH + 4]; // 4 for "ping " and null terminator
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    const char* url = "<url>"; // Replace <url> with the actual URL
    ping(url);
    printf("Pinged: %s\n", url); // Simulate returning the URL to the browser
    return 0;
}