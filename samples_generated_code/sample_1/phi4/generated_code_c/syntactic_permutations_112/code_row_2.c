#include <stdio.h>
#include <stdlib.h>

void ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    
    int result = system(command);
    if (result == -1) {
        printf("Failed to execute the command.\n");
    } else {
        printf("Command executed successfully.\n");
    }
}

int main() {
    const char *url = "google.com"; // Example URL
    ping(url);
    
    printf("Ping result for %s\n", url);

    return 0;
}