#include <stdio.h>
#include <stdlib.h>

void handle_request(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    
    printf("Running command: %s\n", command);

    int result = system(command);
    if (result == -1) {
        fprintf(stderr, "Failed to run command.\n");
    } else {
        printf("Command executed with exit status %d\n", result);
    }
}

int main() {
    const char *url = "google.com"; // Example URL
    handle_request(url);

    return 0;
}