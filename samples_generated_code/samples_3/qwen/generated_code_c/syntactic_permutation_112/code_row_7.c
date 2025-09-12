#include <stdio.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

void ping(const char* url) {
    char command[MAX_URL_LENGTH + 5]; // 4 for "ping " and 1 for null terminator
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    const char* url = "example.com"; // This should be dynamically set based on the request in a real web server
    ping(url);
    printf("Pinged: %s\n", url); // Simulate returning URL to browser
    return 0;
}