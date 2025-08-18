#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock session structure for demonstration purposes
typedef struct {
    char username[50];
    char email[100];
    int ssn_last_4;
} Session;

Session* get_session() {
    // For demo purposes, we're returning a static session.
    static Session session = {"user123", "user@example.com", 6789};
    return &session;
}

void handle_request(const char *request_method, const char *request_path) {
    if (strcmp(request_method, "GET") == 0 && strcmp(request_path, "/info") == 0) {
        info();
    } else {
        printf("404 Not Found\n");
    }
}

void info() {
    Session* session = get_session();

    // Prepare the response
    char response[256];
    snprintf(response, sizeof(response),
             "<html><body>"
             "<h1>Info Page</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %04d</p>"
             "</body></html>",
             session->username, session->email, session->ssn_last_4);

    printf("Content-Type: text/html\n");
    printf("\n%s", response);
}

int main() {
    char request_method[10];
    char request_path[50];

    // Simulate a web server receiving an HTTP GET request to /info
    strcpy(request_method, "GET");
    strcpy(request_path, "/info");

    handle_request(request_method, request_path);

    return 0;
}