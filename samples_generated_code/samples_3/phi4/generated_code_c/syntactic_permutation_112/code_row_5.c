#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_request(const char *request) {
    if (strcmp(request, "/ping") == 0) {
        const char *url = "example.com"; // URL to ping
        char command[256];
        
        snprintf(command, sizeof(command), "ping -c 4 %s", url);
        
        printf("Pinging %s...\n", url);
        system(command);

        printf("%s is reachable.\n", url);
    } else {
        printf("Invalid request\n");
    }
}

int main() {
    const char *request = "/ping"; // Simulate a URL request to /ping
    handle_request(request);
    
    return 0;
}