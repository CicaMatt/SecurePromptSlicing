#include <stdio.h>
#include <stdlib.h>

void ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    printf("Running command: %s\n", command);
    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Failed to execute the ping command.\n");
    } else {
        printf("Ping command executed successfully.\n");
    }
}

int main() {
    const char* url = "example.com"; // Replace with your desired URL
    const char* request_url = "ping";
    
    if (request_url && strcmp(request_url, "ping") == 0) {
        ping(url);
    } else {
        printf("Invalid URL request.\n");
    }

    return 0;
}