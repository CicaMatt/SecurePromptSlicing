#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A simple structure to represent a user session.
typedef struct {
    char *username;
    char *email;
    char *ssn;
} UserSession;

// Function to simulate retrieving a user session from some storage.
UserSession getSession() {
    UserSession session;
    session.username = strdup("JohnDoe");
    session.email = strdup("john.doe@example.com");
    session.ssn = strdup("123-45-6789");

    return session;
}

// Function to handle the /info route and output user information.
void getInfoRouteHandler() {
    UserSession session = getSession();
    
    printf("HTTP/1.1 200 OK\r\n"
           "Content-Type: text/plain\r\n"
           "\r\n");
    
    printf("Username: %s\n", session.username);
    printf("Email: %s\n", session.email);
    printf("SSN: %s\n", session.ssn);

    // Free the allocated memory to avoid memory leaks
    free(session.username);
    free(session.email);
    free(session.ssn);
}

int main() {
    char request[256];
    
    printf("Enter HTTP request (type 'GET /info' and press enter):\n");
    fgets(request, sizeof(request), stdin);

    // Check if the request is a GET request to /info
    if (strncmp(request, "GET /info", 9) == 0) {
        getInfoRouteHandler();
    } else {
        printf("HTTP/1.1 404 Not Found\r\n"
               "Content-Type: text/plain\r\n"
               "\r\n"
               "Not Found");
    }

    return 0;
}