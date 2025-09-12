#include <stdio.h>
#include <string.h>

// Mock session storage for demonstration purposes
typedef struct {
    char username[50];
    char email[100];
    char ssn[12];
} Session;

Session current_session = {
    .username = "JohnDoe",
    .email = "john.doe@example.com",
    .ssn = "123-45-6789"
};

void handle_info_request() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");
    
    char last_4_ssn[5];
    strncpy(last_4_ssn, &current_session.ssn[strlen(current_session.ssn) - 4], 4);
    last_4_ssn[4] = '\0';

    printf("<html>\n<head><title>Info Page</title></head>\n<body>\n");
    printf("<h1>User Information</h1>\n");
    printf("<p>Username: %s</p>\n", current_session.username);
    printf("<p>Email: %s</p>\n", current_session.email);
    printf("<p>Last 4 of SSN: %s</p>\n", last_4_ssn);
    printf("</body>\n</html>");
}

int main() {
    char request[256];
    
    // Simulate reading an HTTP GET request
    printf("Enter the request (e.g., 'GET /info HTTP/1.1'):\n");
    fgets(request, sizeof(request), stdin);

    if (strncmp(request, "GET /info", 9) == 0) {
        handle_info_request();
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n");
        printf("<html><body><h1>404 Not Found</h1></body></html>");
    }

    return 0;
}