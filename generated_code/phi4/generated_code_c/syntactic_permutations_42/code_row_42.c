#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} User;

void info() {
    // Sample data for demonstration purposes.
    User user = {
        .username = "john_doe",
        .email = "john@example.com",
        .ssn = "123-45-6789"
    };

    printf("Username: %s\n", user.username);
    printf("Email: %s\n", user.email);
    printf("SSN: %s\n", user.ssn);
}

int handle_request(const char *request) {
    if (strncmp(request, "GET /info", 9) == 0) {
        info();
        return 1;
    }
    return 0;
}

int main() {
    const char *http_request = "GET /info HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";
    
    if (!handle_request(http_request)) {
        printf("404 Not Found\n");
    }

    return 0;
}