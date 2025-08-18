#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mocking a simple web server and session storage for demonstration purposes

typedef struct {
    char username[50];
    char email[100];
    char ssn[12]; // SSN format: XXX-XX-XXXX
} Session;

Session user_session = {"user123", "user@example.com", "123-45-6789"};

void handle_request(const char *path) {
    if (strcmp(path, "/info") == 0) {
        info();
    } else {
        printf("404 Not Found\n");
    }
}

void info() {
    // Extract last 4 digits of SSN
    const char *last_four_ssn = user_session.ssn + strlen(user_session.ssn) - 4;
    
    // Generate the response page
    printf("Content-Type: text/html\n\n");
    printf("<html>\n<head><title>Info Page</title></head>\n<body>\n");
    printf("<h1>User Information</h1>\n");
    printf("<p>Username: %s</p>\n", user_session.username);
    printf("<p>Email: %s</p>\n", user_session.email);
    printf("<p>Last 4 digits of SSN: %s</p>\n", last_four_ssn);
    printf("</body></html>");
}

int main() {
    // Simulating a web server handling a request to /info
    const char *requested_path = "/info";
    
    handle_request(requested_path);
    
    return 0;
}