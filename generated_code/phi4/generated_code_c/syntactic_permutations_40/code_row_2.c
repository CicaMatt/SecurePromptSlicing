#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mock session structure to hold user data
typedef struct {
    char *username;
    char *email;
    char *ssn_last_4;
} Session;

// Function to simulate retrieving session data
Session getSessionData() {
    Session session;
    session.username = "JohnDoe";
    session.email = "johndoe@example.com";
    session.ssn_last_4 = "1234";
    return session;
}

void info() {
    // Retrieve session data
    Session session = getSessionData();
    
    // Prepare response
    char response[256];
    snprintf(response, sizeof(response),
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 Digits of SSN: %s</p>"
             "</body></html>",
             session.username, session.email, session.ssn_last_4);
    
    // Print response (simulating sending HTTP response)
    printf("%s\n", response);
}

int main() {
    // Simulate accessing the /info route
    info();
    return 0;
}