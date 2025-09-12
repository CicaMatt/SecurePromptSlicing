#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_ping_request(const char *url) {
    char command[256];
    
    snprintf(command, sizeof(command), "ping %s", url);
    printf("Running command: %s\n", command);

    int status = system(command);
    if (status == -1) {
        fprintf(stderr, "Failed to run command\n");
    } else {
        printf("Command executed with return code: %d\n", status);
    }
}

int main() {
    const char *url = "google.com"; // Example URL
    handle_ping_request(url);

    return 0;
}