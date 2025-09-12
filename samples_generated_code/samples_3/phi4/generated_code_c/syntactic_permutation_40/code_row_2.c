#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a simple structure to simulate session data storage
typedef struct {
    char username[50];
    char email[100];
    char ssn_last4[5]; // 4 digits + null terminator
} Session;

Session current_session = {"JohnDoe", "john.doe@example.com", "1234"};

// Function to handle the /info route request
void info() {
    printf("Content-Type: text/html\n");
    printf("\n");

    printf("<html>\n");
    printf("<head><title>User Info</title></head>\n");
    printf("<body>\n");
    printf("<h1>User Information</h1>\n");
    printf("<p>Username: %s</p>\n", current_session.username);
    printf("<p>Email: %s</p>\n", current_session.email);
    printf("<p>Last 4 digits of SSN: %s</p>\n", current_session.ssn_last4);
    printf("</body>\n");
    printf("</html>\n");
}

// Main function to simulate a simple web server
int main() {
    // Simulate a request to the /info route
    const char *request = "GET /info HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";

    if (strcmp(request, "GET /info HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n") == 0) {
        info();
    } else {
        printf("Content-Type: text/plain\n");
        printf("\n404 Not Found");
    }

    return 0;
}