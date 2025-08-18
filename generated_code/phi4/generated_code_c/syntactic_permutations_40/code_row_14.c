#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session getSession() {
    // Mock session data
    Session session = {
        .username = "john_doe",
        .email = "john@example.com",
        .ssn = "123-45-6789"
    };
    return session;
}

void handleRequest(const char *route) {
    if (strcmp(route, "/info") == 0) {
        Session session = getSession();
        
        // Extract last 4 digits of SSN
        char ssnLastFour[5];
        sscanf(session.ssn + strlen(session.ssn) - 4, "%4s", ssnLastFour);

        // Create response HTML
        char response[BUFFER_SIZE];
        snprintf(response, BUFFER_SIZE,
                 "<html><head><title>Info Page</title></head>"
                 "<body>"
                 "<h1>User Information</h1>"
                 "<p>Username: %s</p>"
                 "<p>Email: %s</p>"
                 "<p>Last 4 digits of SSN: %s</p>"
                 "</body></html>",
                 session.username, session.email, ssnLastFour);

        // Send response (mocking with printf)
        printf("%s\n", response);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulate a GET request to the /info route
    handleRequest("/info");

    return 0;
}