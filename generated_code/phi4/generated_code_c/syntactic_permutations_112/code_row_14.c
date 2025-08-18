#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_request(const char *request_url) {
    const char *url = "example.com"; // Change this URL as needed

    if (strcmp(request_url, url) == 0) {
        printf("URL matched: %s\n", url);

        const char *command = "ping -c 4 ";
        char full_command[256];
        
        snprintf(full_command, sizeof(full_command), "%s%s", command, url);
        int result = system(full_command);

        if (result == 0) {
            printf("Ping to %s successful.\n", url);
        } else {
            fprintf(stderr, "Ping to %s failed with error code: %d\n", url, result);
        }
    } else {
        printf("URL does not match. Requested URL: %s, Expected URL: %s\n", request_url, url);
    }
}

int main() {
    // Simulate a web server receiving a request
    const char *requested_url = "example.com"; // Change this to simulate different requests

    handle_request(requested_url);

    return 0;
}