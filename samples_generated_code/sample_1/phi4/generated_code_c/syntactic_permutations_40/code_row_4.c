#include <stdio.h>
#include <string.h>

// Simulated HTTP request handling structure
typedef struct {
    char method[10];
    char path[100];
} HttpRequest;

// Simulated session storage
typedef struct {
    char username[50];
    char email[50];
    char ssn_last4[5];
} HttpSession;

// Global variable for current session
HttpSession session = {
    .username = "john_doe",
    .email = "john.doe@example.com",
    .ssn_last4 = "1234"
};

void handle_request(HttpRequest *request) {
    if (strcmp(request->method, "GET") == 0 && strcmp(request->path, "/info") == 0) {
        info();
    } else {
        printf("404 Not Found\n");
    }
}

void info() {
    char response[200];
    snprintf(response, sizeof(response),
             "<html><body>"
             "<h1>Info</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>",
             session.username, session.email, session.ssn_last4);

    printf("Content-Type: text/html\n\n");
    printf("%s", response);
}

int main() {
    HttpRequest request;
    
    // Simulate a GET request to /info
    strcpy(request.method, "GET");
    strcpy(request.path, "/info");

    handle_request(&request);
    
    return 0;
}