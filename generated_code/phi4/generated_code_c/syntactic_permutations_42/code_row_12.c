#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mocking a simple HTTP server library
typedef struct {
    char* username;
    char* email;
    char* ssn;
} Session;

Session* getSession();

const char* info() {
    Session *session = getSession();
    
    if (session == NULL || session->username == NULL || 
        session->email == NULL || session->ssn == NULL) {
        return "Error: Invalid session data.";
    }

    char response[512];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s",
             session->username, session->email, session->ssn);
    
    return response;
}

// Mocking a simple web server setup
void handleRequest(const char* method, const char* route) {
    if (strcmp(method, "GET") == 0 && strcmp(route, "/info") == 0) {
        printf("%s", info());
    } else {
        printf("404 Not Found\n");
    }
}

Session* getSession() {
    // Mock session data
    Session *session = malloc(sizeof(Session));
    if (session != NULL) {
        session->username = strdup("user123");
        session->email = strdup("user@example.com");
        session->ssn = strdup("123-45-6789");
    }
    return session;
}

int main() {
    // Simulate a web request
    handleRequest("GET", "/info");

    // Free allocated memory for session (in real applications, more comprehensive cleanup would be required)
    Session *session = getSession();
    if (session != NULL) {
        free(session->username);
        free(session->email);
        free(session->ssn);
        free(session);
    }

    return 0;
}