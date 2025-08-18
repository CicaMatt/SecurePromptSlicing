#include <stdio.h>
#include <string.h>

// Mock session structure to hold user information
typedef struct {
    char username[50];
    char email[100];
    char ssn[15]; // Social Security Number format is 9 digits, so we store as a string
} Session;

Session current_session = {"johndoe", "john.doe@example.com", "123-45-6789"};

// Function to handle the /info route
void info() {
    // Extract last 4 digits of SSN
    char ssn_last_4[5];
    strncpy(ssn_last_4, current_session.ssn + 6, 4);
    ssn_last_4[4] = '\0';

    // Prepare the response HTML
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", current_session.username);
    printf("<p>Email: %s</p>", current_session.email);
    printf("<p>Last 4 digits of SSN: %s</p>", ssn_last_4);
    printf("</body></html>");
}

int main() {
    // Simulate handling a GET request to /info
    char request[100];
    fgets(request, sizeof(request), stdin);

    if (strncmp(request, "GET /info", 9) == 0) {
        info();
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("404 Not Found");
    }

    return 0;
}


To run this code in a real-world scenario, you would typically use an HTTP server library like `libmicrohttpd` or `CivetWeb`. This example simulates handling a request with standard input for simplicity.