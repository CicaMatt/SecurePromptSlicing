#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_ping_request(const char *url) {
    char command[256];
    
    snprintf(command, sizeof(command), "ping %s", url);
    printf("Running command: %s\n", command);

    int result = system(command);
    if (result == -1) {
        fprintf(stderr, "Failed to run ping command.\n");
    } else {
        printf("Ping command executed with return code: %d\n", result);
    }
}

int main() {
    const char *url = "google.com"; // URL can be changed as needed
    handle_ping_request(url);

    return 0;
}