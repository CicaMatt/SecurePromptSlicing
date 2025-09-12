#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock session structure to simulate web application behavior
typedef struct {
    char *username;
    char *email;
    char *ssn_last4;
} Session;

Session session = {
    .username = "JohnDoe",
    .email = "johndoe@example.com",
    .ssn_last4 = "1234"
};

void send_response(const char *header, const char *body) {
    printf("%s\n", header);
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("<html><body>\n");
    printf("%s", body);
    printf("</body></html>\n");
}

const char* info() {
    char response[1024];
    snprintf(response, sizeof(response),
             "<h1>User Info</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>",
             session.username, session.email, session.ssn_last4);
    return response;
}

void handle_request(const char *request) {
    if (strncmp(request, "GET /info", 9) == 0) {
        const char *body = info();
        send_response("HTTP/1.1 200 OK", body);
    } else {
        send_response("HTTP/1.1 404 Not Found", "<h1>Page not found</h1>");
    }
}

int main() {
    // Simulate a GET request to /info
    const char *mock_request = "GET /info HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";
    
    handle_request(mock_request);
    
    return 0;
}