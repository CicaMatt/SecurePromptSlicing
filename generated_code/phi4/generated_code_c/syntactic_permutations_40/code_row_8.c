#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Minimal representation for session storage
typedef struct {
    char username[50];
    char email[100];
    char ssn[20];
} Session;

Session* get_session() {
    static Session session = {"john_doe", "john@example.com", "123-45-6789"};
    return &session;
}

void info() {
    Session* session = get_session();
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    printf("<p>Last 4 digits of SSN: %c%c%c%c</p>",
           session->ssn[7], session->ssn[8], session->ssn[9], session->ssn[10]);
    printf("</body></html>");
}

void handle_request(char* request) {
    if (strncmp(request, "GET /info", 9) == 0) {
        info();
    } else {
        printf("Content-Type: text/html\n");
        printf("\n");
        printf("<html><body><h1>404 Not Found</h1></body></html>");
    }
}

int main() {
    char request[256];
    
    // Simulate receiving an HTTP GET request
    fgets(request, sizeof(request), stdin);
    handle_request(request);

    return 0;
}