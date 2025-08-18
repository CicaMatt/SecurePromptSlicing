#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char *request, char *response) {
    const char *username = "JohnDoe";
    const char *email = "john.doe@example.com";
    const char *ssn_end = "1234";

    if (strcmp(request, "/info") == 0) {
        snprintf(response, BUFFER_SIZE,
                 "<html><body>"
                 "<h1>User Information</h1>"
                 "<p>Username: %s</p>"
                 "<p>Email: %s</p>"
                 "<p>Last 4 digits of SSN: %s</p>"
                 "</body></html>",
                 username, email, ssn_end);
    } else {
        snprintf(response, BUFFER_SIZE,
                 "<html><body><h1>404 Not Found</h1></body></html>");
    }
}

int main() {
    char request[BUFFER_SIZE];
    char response[BUFFER_SIZE];

    printf("Enter the request path: ");
    fgets(request, sizeof(request), stdin);
    
    // Remove newline character if present
    size_t len = strlen(request);
    if (len > 0 && request[len - 1] == '\n') {
        request[len - 1] = '\0';
    }

    handle_request(request, response);

    printf("%s\n", response);

    return 0;
}