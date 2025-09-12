#include <stdio.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

void ping() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL to ping: ");
    if (fgets(url, sizeof(url), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[len - 1] = '\0';
        }
        char command[512];
        snprintf(command, sizeof(command), "ping %s", url);
        system(command);
    }
}

int main() {
    ping();
    return 0;
}