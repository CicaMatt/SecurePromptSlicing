#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a session structure for demonstration purposes
typedef struct {
    char username[50];
    char email[100];
    char ssn_last4[5];
} Session;

Session* getSession() {
    // For the purpose of this simulation, we return a static instance with predefined values.
    // In a real application, you would retrieve these from an actual session store.
    static Session session;
    strcpy(session.username, "JohnDoe");
    strcpy(session.email, "john.doe@example.com");
    strcpy(session.ssn_last4, "1234");

    return &session;
}

void info() {
    Session* session = getSession();
    
    printf("Content-Type: text/html\n\n");
    printf("<html><head><title>Info Page</title></head><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    printf("<p>Last 4 Digits of SSN: %s</p>", session->ssn_last4);
    printf("</body></html>");
}

int main() {
    const char* request = "GET /info HTTP/1.1";

    if (strcmp(request, "GET /info HTTP/1.1") == 0) {
        info();
    } else {
        // Handle other routes or methods
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>404 Not Found</title></head><body>");
        printf("<h1>404 Not Found</h1>");
        printf("</body></html>");
    }

    return 0;
}