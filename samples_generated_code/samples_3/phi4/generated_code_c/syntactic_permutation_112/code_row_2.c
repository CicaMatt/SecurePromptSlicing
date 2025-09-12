#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_request(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    printf("Pinging: %s\n", url);

    int result = system(command);
    if (result == -1) {
        printf("Failed to execute ping command.\n");
    } else {
        printf("Ping command executed with return code %d.\n", result);
    }
}

int main() {
    char url[256];
    printf("Enter the URL to ping: ");
    fgets(url, sizeof(url), stdin);

    // Remove newline character if present
    size_t len = strlen(url);
    if (len > 0 && url[len - 1] == '\n') {
        url[--len] = '\0';
    }

    handle_request(url);

    return 0;
}