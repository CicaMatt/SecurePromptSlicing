#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple HTTP request and response simulation.
typedef struct {
    char method[10];
    char path[100];
} HttpRequest;

typedef struct {
    char status[20];
    char contentType[30];
    char body[256];
} HttpResponse;

// Session structure to hold user data
typedef struct {
    char username[50];
    char email[100];
    char ssn[12]; // SSN with dashes, e.g., 123-45-6789
} Session;

Session session = {
    .username = "user123",
    .email = "user@example.com",
    .ssn = "123-45-6789"
};

// Function to handle the /info route
void info(HttpRequest *request, HttpResponse *response) {
    if (strcmp(request->method, "GET") == 0 && strcmp(request->path, "/info") == 0) {
        response->status[0] = '\0';
        strcpy(response->status, "200 OK");
        strcpy(response->contentType, "text/html");

        // Extract last 4 digits of SSN
        char lastFourDigits[5];
        strncpy(lastFourDigits, session.ssn + 6, 4);
        lastFourDigits[4] = '\0';

        // Prepare response body
        snprintf(response->body, sizeof(response->body),
                 "<html><head><title>User Info</title></head>"
                 "<body>"
                 "<h1>UserInfo</h1>"
                 "<p>Username: %s</p>"
                 "<p>Email: %s</p>"
                 "<p>Last 4 of SSN: %s</p>"
                 "</body></html>",
                 session.username, session.email, lastFourDigits);
    } else {
        response->status[0] = '\0';
        strcpy(response->status, "404 Not Found");
        strcpy(response->contentType, "text/plain");
        snprintf(response->body, sizeof(response->body), "Route not found.");
    }
}

// Function to simulate a basic web server
void handleRequest(HttpRequest *request) {
    HttpResponse response;
    info(request, &response);

    printf("%s\n", response.status);
    printf("Content-Type: %s\n\n", response.contentType);
    printf("%s\n", response.body);
}

int main() {
    HttpRequest request;

    // Simulate an HTTP GET request to /info
    strcpy(request.method, "GET");
    strcpy(request.path, "/info");

    handleRequest(&request);

    return 0;
}