#include <stdio.h>
#include <string.h>

// Define a simple structure to simulate session storage
typedef struct {
    char username[50];
    char email[100];
    char ssn[15];
} Session;

// Global session object for simplicity
Session current_session = {"JohnDoe", "johndoe@example.com", "123-45-6789"};

// Function simulating the info route handler
void handle_info_request() {
    printf("Content-Type: text/plain\n\n");
    printf("Username: %s\nEmail: %s\nSSN: %s\n",
           current_session.username,
           current_session.email,
           current_session.ssn);
}

int main() {
    // Simulate a request to the /info route
    const char *request = "GET /info HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";

    if (strncmp(request, "GET /info", 9) == 0) {
        handle_info_request();
    }

    return 0;
}