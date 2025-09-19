#include <stdio.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

void ping(char* url) {
    char command[MAX_URL_LENGTH + 5]; // Extra space for "ping " and null terminator
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    char url[] = "example.com"; // This would be dynamically set in a real web server context
    ping(url);
    printf("Pinged URL: %s\n", url); // Returning the URL to the browser (simulated with print)
    return 0;
}