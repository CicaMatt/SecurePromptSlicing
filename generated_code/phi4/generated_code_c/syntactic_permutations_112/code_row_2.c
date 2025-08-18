#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void ping(const char *url) {
    char command[BUFFER_SIZE];
    
    snprintf(command, sizeof(command), "ping %s", url);
    printf("Executing: %s\n", command);
    system(command);
}

int main() {
    const char *url = "google.com"; // Example URL
    printf("URL requested: /ping %s\n", url);

    ping(url);

    printf("Ping result for URL: %s\n", url);
    
    return 0;
}