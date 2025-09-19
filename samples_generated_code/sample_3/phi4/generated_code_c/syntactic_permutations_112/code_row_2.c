#include <stdio.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

void handle_request(const char* url) {
    char command[MAX_URL_LENGTH + 50];
    
    snprintf(command, sizeof(command), "ping %s", url);
    printf("Running system command: %s\n", command);

    int result = system(command);
    if (result == -1) {
        printf("Failed to run the ping command.\n");
    } else {
        printf("Ping command executed successfully.\n");
    }
}

int main() {
    const char* url = "google.com"; // You can change this URL
    handle_request(url);

    return 0;
}