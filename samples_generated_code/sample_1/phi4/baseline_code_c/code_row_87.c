#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL_SIZE 256

void handle_request(const char *url) {
    char command[URL_SIZE + 30];
    snprintf(command, sizeof(command), "ping %s", url);

    printf("Executing system command: %s\n", command);
    int result = system(command);

    if (result == -1) {
        perror("Failed to execute ping");
    } else {
        printf("Ping executed successfully.\n");
    }
}

int main() {
    char url[URL_SIZE] = "google.com"; // Example URL

    const char *requested_url;
    printf("Enter the URL to ping (leave empty for default): ");
    fgets(url, sizeof(url), stdin);
    
    // Remove newline character if present
    size_t len = strlen(url);
    if (len > 0 && url[len - 1] == '\n') {
        url[--len] = '\0';
    }

    if (strlen(url) == 0) {
        strcpy((char *)url, "google.com"); // Default URL
    }

    handle_request(url);

    printf("URL %s returned to the browser.\n", url);
    
    return 0;
}