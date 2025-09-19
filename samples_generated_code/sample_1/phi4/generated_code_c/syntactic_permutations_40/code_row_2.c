#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "johndoe"
#define EMAIL "john.doe@example.com"
#define SSN_LAST_FOUR "1234"

const char* info() {
    static char response[512];
    snprintf(response, sizeof(response),
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 Digits of SSN: %s</p>"
             "</body></html>",
             USERNAME, EMAIL, SSN_LAST_FOUR);
    return response;
}

void handle_request(const char *request) {
    if (strcmp(request, "GET /info") == 0) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
        printf("%s", info());
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\n");
        printf("Not Found");
    }
}

int main() {
    char request[128];
    
    printf("Enter the request: ");
    fgets(request, sizeof(request), stdin);
    request[strcspn(request, "\r\n")] = '\0';  // Remove newline character

    handle_request(request);

    return 0;
}